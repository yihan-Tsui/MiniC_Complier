// AssemblyGenerator.h
#ifndef MINI_C_ASSEMBLY_GENERATOR_H
#define MINI_C_ASSEMBLY_GENERATOR_H

#include "ir.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <ostream>

class AssemblyGenerator {
public:
    explicit AssemblyGenerator(const std::vector<Quad> &quads);
    std::string generate();
private:
    const std::vector<Quad> &quads_;
    std::unordered_map<std::string, int> localOffset_;
    std::unordered_map<std::string, int> tempOffset_;
    int stackSize_;
    void allocateStack();
    void emitPrologue(std::ostream &os) const;
    void emitEpilogue(std::ostream &os) const;
    void emitInstruction(const Quad &q, std::ostream &os) const;
    void loadOperand(const std::string &name, std::ostream &os) const;
    void storeResult(const std::string &name, std::ostream &os) const;
};

#endif // MINI_C_ASSEMBLY_GENERATOR_H
