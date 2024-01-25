#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

// AST node for binary operations
struct BinaryOperationNode
{
    char op;
    boost::variant<int, BinaryOperationNode> left;
    boost::variant<int, BinaryOperationNode> right;
};

// AST node for unary operations
struct UnaryOperationNode
{
    char op;
    boost::variant<int, UnaryOperationNode> operand;
};

// AST node for numeric values
struct ValueNode
{
    int value;
};

// AST node for parameter index
struct ParameterIndexNode
{
    int index;
};

// AST node for parameter setting
struct ParameterSettingNode
{
    ParameterIndexNode index;
    int value;
};

// AST node for expressions
typedef boost::variant<ValueNode, BinaryOperationNode, UnaryOperationNode, ParameterIndexNode, ParameterSettingNode> ExpressionNode;

// ExpressionPrinter visitor for displaying AST nodes
struct ExpressionPrinter : boost::static_visitor<std::string>
{
    std::string operator()(const BinaryOperationNode &binaryOp) const
    {
        return "(" + boost::apply_visitor(*this, binaryOp.left) + " " + binaryOp.op + " " + boost::apply_visitor(*this, binaryOp.right) + ")";
    }

    std::string operator()(const UnaryOperationNode &unaryOp) const
    {
        return unaryOp.op + "(" + boost::apply_visitor(*this, unaryOp.operand) + ")";
    }

    std::string operator()(const ValueNode &value) const
    {
        return std::to_string(value.value);
    }

    std::string operator()(const ParameterIndexNode &paramIndex) const
    {
        return "#" + std::to_string(paramIndex.index);
    }

    std::string operator()(const ParameterSettingNode &paramSetting) const
    {
        return "#" + std::to_string(paramSetting.index.index) + " = " + std::to_string(paramSetting.value);
    }
};

// Symbol table for variable storage
class SymbolTable
{
private:
    std::unordered_map<std::string, double> symbolTable;

public:
    // Set the value of a variable in the symbol table
    void setVariable(const std::string &name, double value)
    {
        symbolTable[name] = value;
    }

    // Get the value of a variable from the symbol table
    double getVariable(const std::string &name)
    {
        if (symbolTable.find(name) != symbolTable.end())
        {
            return symbolTable[name];
        }
        else
        {
            // Handle error: variable not found
            std::cerr << "Error: Variable '" << name << "' not found." << std::endl;
            return 0.0; // Placeholder value, you might want to throw an exception or handle differently
        }
    }
};

// RS274/NGC Interpreter
class RS274NGCInterpreter
{
private:
    SymbolTable symbolTable;

public:
    // Execute an expression node
    double executeExpression(const ExpressionNode &node)
    {
        struct ExpressionEvaluator : boost::static_visitor<double>
        {
            RS274NGCInterpreter &interpreter;

            ExpressionEvaluator(RS274NGCInterpreter &interpreter) : interpreter(interpreter) {}

            double operator()(const BinaryOperationNode &binaryOp) const
            {
                double left = boost::apply_visitor(*this, binaryOp.left);
                double right = boost::apply_visitor(*this, binaryOp.right);

                switch (binaryOp.op)
                {
                case '+':
                    return left + right;
                case '-':
                    return left - right;
                case '*':
                    return left * right;
                case '/':
                    return left / right;
                default:
                    std::cerr << "Error: Unknown binary operation." << std::endl;
                    return 0.0; // Placeholder value
                }
            }

            double operator()(const UnaryOperationNode &unaryOp) const
            {
                double operand = boost::apply_visitor(*this, unaryOp.operand);

                switch (unaryOp.op)
                {
                case 'a':
                    return std::abs(operand);
                case 's':
                    return std::sin(operand);
                case 'c':
                    return std::cos(operand);
                case 't':
                    return std::tan(operand);
                // Add more unary operations as needed
                default:
                    std::cerr << "Error: Unknown unary operation." << std::endl;
                    return 0.0; // Placeholder value
                }
            }

            double operator()(const ValueNode &value) const
            {
                return value.value;
            }

            double operator()(const ParameterIndexNode &paramIndex) const
            {
                return interpreter.symbolTable.getVariable("#" + std::to_string(paramIndex.index));
            }

            double operator()(const ParameterSettingNode &paramSetting) const
            {
                interpreter.symbolTable.setVariable("#" + std::to_string(paramSetting.index.index), paramSetting.value);
                return paramSetting.value;
            }
        };

        return boost::apply_visitor(ExpressionEvaluator(*this), node);
    }

    // Execute a sequence of expressions
    void executeCode(const std::vector<ExpressionNode> &code)
    {
        for (const auto &expression : code)
        {
            executeExpression(expression);
        }
    }
};

// Grammar definition
template <typename Iterator>
struct RS274NGCGrammar : qi::grammar<Iterator, std::vector<ExpressionNode>(), ascii::space_type>
{
    RS274NGCGrammar(RS274NGCInterpreter &interpreter) : RS274NGCGrammar::base_type(program), interpreter(interpreter)
    {
        using qi::_1;
        using qi::_val;

        program %= *(expression);

        expression %= term >> *(('+' >> term) | ('-' >> term));
        term %= factor >> *(('*' >> factor) | ('/' >> factor));
        factor %= primary >> *(qi::char_("+-") >> primary);
        primary %= qi::int_ | parameter_setting | '(' >> expression >> ')' | unary_operation | mid_line_word | mid_line_letter;

        unary_operation %= (qi::lit("abs") | qi::lit("acos") | qi::lit("asin") | qi::lit("atan") | qi::lit("cos") |
                            qi::lit("exp") | qi::lit("fix") | qi::lit("fup") | qi::lit("ln") | qi::lit("round") |
                            qi::lit("sin") | qi::lit("sqrt") | qi::lit("tan")) >>
                           '(' >> expression >> ')';

        parameter_index %= qi::int_;
        parameter_setting %= qi::lit('#') >> parameter_index >> qi::lit('=') >> qi::int_;

        arc_tangent_combo %= qi::lit("atan") >> expression >> qi::lit('/') >> expression;
        binary_operation %= binary_operation1 | binary_operation2 | binary_operation3;
        binary_operation1 %= qi::lit("power");
        binary_operation2 %= qi::lit("divided_by") | qi::lit("modulo") | qi::lit("times");
        binary_operation3 %= qi::lit("and") | qi::lit("xor") | qi::lit("minus") | qi::lit("or") | qi::lit("plus");
        comment %= message | ordinary_comment;
        comment_character = qi::char_;
        digit %= qi::char_("0-9");
        expression %= qi::lit('[') >> real_value >> *(binary_operation >> real_value) >> qi::lit(']');
        mid_line_letter %= qi::char_("a-zA-Z");
        mid_line_word %= mid_line_letter >> real_value;
        ordinary_comment %= qi::lit('(') >> *comment_character >> qi::lit(')');
        ordinary_unary_combo %= ordinary_unary_operation >> expression;
        ordinary_unary_operation %= qi::lit("abs") | qi::lit("acos") | qi::lit("asin") | qi::lit("cos") |
                                    qi::lit("exp") | qi::lit("fix_down") | qi::lit("fix_up") | qi::lit("ln") |
                                    qi::lit("round") | qi::lit("sin") | qi::lit("sqrt") | qi::lit("tan");
        parameter_index %= real_value;
        parameter_setting %= qi::lit('#') >> parameter_index >> qi::lit('=') >> real_value;

        BOOST_SPIRIT_DEBUG_NODES((program)(expression)(term)(factor)(primary)(unary_operation)(parameter_index)(parameter_setting)(arc_tangent_combo)(binary_operation)(binary_operation1)(binary_operation2)(binary_operation3)(comment)(comment_character)(digit)(expression)(mid_line_letter)(mid_line_word)(ordinary_comment)(ordinary_unary_combo)(ordinary_unary_operation));
    }

    qi::rule<Iterator, std::vector<ExpressionNode>(), ascii::space_type> program;
    qi::rule<Iterator, ExpressionNode(), ascii::space_type> expression, term, factor, primary, unary_operation;
    qi::rule<Iterator, ParameterIndexNode(), ascii::space_type> parameter_index;
    qi::rule<Iterator, ParameterSettingNode(), ascii::space_type> parameter_setting;
    qi::rule<Iterator, void(), ascii::space_type> arc_tangent_combo, binary_operation, binary_operation1, binary_operation2, binary_operation3,
        comment, ordinary_comment, ordinary_unary_combo, ordinary_unary_operation;
    qi::rule<Iterator, char(), ascii::space_type> comment_character;
    qi::rule<Iterator, char(), ascii::space_type> digit;
    qi::rule<Iterator, void(), ascii::space_type> mid_line_letter, mid_line_word;

    qi::rule<Iterator, std::string(), ascii::space_type> message;

    // Real value parser for parameter and constant values
    qi::real_parser<double, qi::strict_real_policies<double>> real_value;

    RS274NGCInterpreter &interpreter;
};

int main()
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator Iterator;

    RS274NGCInterpreter interpreter;
    RS274NGCGrammar<Iterator> parser(interpreter);

    std::string input = "abs(3 * (4 + 5)) #1 = 42 atan 3 / 4 divided_by 5";

    Iterator iter = input.begin();
    Iterator end = input.end();

    std::vector<ExpressionNode> result;

    bool success = qi::phrase_parse(iter, end, parser, space, result);

    if (success && iter == end)
    {
        std::cout << "Parsing succeeded.\n";

        // Displaying the parsed AST
        for (const auto &node : result)
        {
            std::cout << "Node: " << boost::apply_visitor(ExpressionPrinter(), node) << std::endl;
        }

        // Execute the parsed code
        interpreter.executeCode(result);
    }
    else
    {
        std::cout << "Parsing failed.\n";
    }

    return 0;
}
