// type.h
#ifndef MINI_C_TYPE_H
#define MINI_C_TYPE_H

#include <memory>
#include <string>
#include <vector>
#include "ast.h"  // for TypeSpecifier, SourceLoc

// 前向声明
class Type;
using TypePtr = std::shared_ptr<Type>;

// 抽象基类
class Type {
public:
    virtual ~Type() = default;
    virtual bool equals(const Type* other) const = 0;
    virtual std::string toString() const = 0;
};

// --------- 基本类型 ---------
class BasicType : public Type {
public:
    explicit BasicType(TypeSpecifier spec) : spec_(spec) {}
    bool equals(const Type* other) const override {
        auto o = dynamic_cast<const BasicType*>(other);
        return o && o->spec_ == spec_;
    }
    std::string toString() const override {
        switch (spec_) {
            case TS_VOID:      return "void";
            case TS_CHAR:      return "char";
            case TS_SHORT:     return "short";
            case TS_INT:       return "int";
            case TS_LONG:      return "long";
            case TS_FLOAT:     return "float";
            case TS_DOUBLE:    return "double";
            case TS_SIGNED:    return "signed";
            case TS_UNSIGNED:  return "unsigned";
            case TS_BOOL:      return "bool";
            case TS_COMPLEX:   return "_Complex";
            case TS_IMAGINARY: return "_Imaginary";
            case TS_TYPE_NAME: return "typedef-name";
        }
        return "unknown";
    }
    TypeSpecifier spec() const { return spec_; }
private:
    TypeSpecifier spec_;
};

// --------- 指针类型 ---------
class PointerType : public Type {
public:
    explicit PointerType(TypePtr pointee) : pointee_(std::move(pointee)) {}
    bool equals(const Type* other) const override {
        auto o = dynamic_cast<const PointerType*>(other);
        return o && pointee_->equals(o->pointee_.get());
    }
    std::string toString() const override {
        return pointee_->toString() + "*";
    }
    TypePtr pointee() const { return pointee_; }
private:
    TypePtr pointee_;
};

// --------- 数组类型 ---------
class ArrayType : public Type {
public:
    // size<0 表示未知维度
    ArrayType(TypePtr elem, int size = -1)
      : elem_(std::move(elem)), size_(size) {}
    bool equals(const Type* other) const override {
        auto o = dynamic_cast<const ArrayType*>(other);
        return o && elem_->equals(o->elem_.get()) && size_ == o->size_;
    }
    std::string toString() const override {
        return elem_->toString() + "[" + (size_ >= 0 ? std::to_string(size_) : "") + "]";
    }
    TypePtr element() const { return elem_; }
    int size() const { return size_; }
private:
    TypePtr elem_;
    int      size_;
};

// --------- 函数类型 ---------
class FunctionType : public Type {
public:
    FunctionType(TypePtr ret, std::vector<TypePtr> params, bool vararg = false)
      : ret_(std::move(ret)), params_(std::move(params)), isVarArg_(vararg) {}
    bool equals(const Type* other) const override {
        auto o = dynamic_cast<const FunctionType*>(other);
        if (!o || isVarArg_ != o->isVarArg_ || !ret_->equals(o->ret_.get())
            || params_.size() != o->params_.size())
            return false;
        for (size_t i = 0; i < params_.size(); ++i)
            if (!params_[i]->equals(o->params_[i].get()))
                return false;
        return true;
    }
    std::string toString() const override {
        std::string s = ret_->toString() + "(";
        for (size_t i = 0; i < params_.size(); ++i) {
            if (i) s += ", ";
            s += params_[i]->toString();
        }
        if (isVarArg_) {
            if (!params_.empty()) s += ", ";
            s += "...";
        }
        s += ")";
        return s;
    }
    TypePtr returnType() const { return ret_; }
    const std::vector<TypePtr>& params() const { return params_; }
    bool isVarArg() const { return isVarArg_; }
private:
    TypePtr ret_;
    std::vector<TypePtr> params_;
    bool isVarArg_;
};

#endif // MINI_C_TYPE_H
