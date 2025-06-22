// symbol.h
#ifndef MINI_C_SYMBOL_H
#define MINI_C_SYMBOL_H

#include <string>
#include <unordered_map>
#include <memory>
#include "type.h"      // 预计后面定义 Type 类
#include "ast.h"

// 一条符号 信息：名称、类型、声明位置、存储类别等
struct Symbol {
    std::string name;
    std::shared_ptr<Type> type;
    StorageClass storage;
    SourceLoc    decl_loc;    // 定义时的行列

    Symbol(const std::string& n,
           std::shared_ptr<Type> t,
           StorageClass s,
           SourceLoc loc)
        : name(n), type(std::move(t)), storage(s), decl_loc(loc) {}
};

// 作用域：一组符号 + 指向外层作用域
class Scope : public std::enable_shared_from_this<Scope> {
public:
    explicit Scope(std::shared_ptr<Scope> parent = nullptr)
      : parent_(std::move(parent)) {}
    bool insert(const Symbol& sym) {
        auto [it, ok] = syms_.emplace(sym.name, sym);
        return ok;
    }
    Symbol* lookup(const std::string& name) {
        auto it = syms_.find(name);
        if (it != syms_.end()) return &it->second;
        if (parent_) return parent_->lookup(name);
        return nullptr;
    }
    std::shared_ptr<Scope> push() {
        return std::make_shared<Scope>(shared_from_this());
    }
    std::shared_ptr<Scope> pop() {
        return parent_;
    }

private:
    std::unordered_map<std::string, Symbol> syms_;
    std::shared_ptr<Scope> parent_;
};

#endif // MINI_C_SYMBOL_H
