#pragma once

#include <string>
#include <unordered_map>

namespace Printer{

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
}