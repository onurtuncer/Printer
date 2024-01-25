#pragma once 

#include "Interpreter.h"

class PrintRunner {           
    public:
        explicit PrintRunner();
        virtual ~PrintRunner();

        void Run(const std::string &program);

    private:
        typedef std::string::const_iterator Iterator;
        RS274NGCGrammar<Iterator> m_Parser;
};
