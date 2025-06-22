cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        ast.cpp
        ast.h
        lex.yy.cpp
        mini_c.tab.hpp
        mini_c.tab.cpp
        stack.hh
        symbol.cpp
        symbol.h
        semantic.cpp
        semantic.h
        type.cpp
        type.h
        ir.cpp
        ir.h
        interpreter.cpp
        interpreter.h
        AssemblyGenerator.cpp
        AssemblyGenerator.h
        SimpleAssembler.cpp
        ObjectFileGenerator.cpp
        ObjectFileGenerator.h
        InstructionEncoder.cpp
        InstructionEncoder.h
        test.cpp
        PrettyPrinter.cpp
        PrettyPrinter.h
)
