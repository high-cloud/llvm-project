//===--- ExpanderConvertCheck.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ExpanderConvertCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Transformer/Stencil.h"
namespace clang::tidy::misc {

using namespace clang::ast_matchers;
using ::clang::transformer::addInclude;
using ::clang::transformer::applyFirst;
using ::clang::transformer::callArgs;
using ::clang::transformer::cat;
using ::clang::transformer::changeTo;
using ::clang::transformer::makeRule;
using ::clang::transformer::member;
using ::clang::transformer::node;
using namespace ::clang::transformer;
using ::clang::transformer::RewriteRuleWith;
using std::string;

llvm::StringRef e = "expr", m = "member";
llvm::StringRef call_e = "callExpr";
auto child_call =
    cxxMemberCallExpr(on(expr().bind(e)), callee(memberExpr().bind(m)),
                      hasAncestor(functionDecl(hasAnyParameter(hasName("gb")))))
        .bind(call_e);

// gb.fun(..) -> ib->fun(..)
auto gb2ib = makeRule(child_call,
                      changeTo(cat("ib->", member(std::string(m)), "(",
                                   callArgs(string(call_e)), ")")),
                      cat("change ir builder expr"));

// inputs[i] -> ib->Input(i)
auto inputs_convert = makeRule(
    cxxOperatorCallExpr(
        hasOverloadedOperatorName("[]"),
        hasArgument(0, declRefExpr(hasDeclaration(varDecl(hasName("inputs"))))),
        hasArgument(1, expr().bind("idx"))),
    changeTo(cat("ib->input", "(", node("idx"), ")")), cat("input converter"));


ExpanderConvertCheck::ExpanderConvertCheck(StringRef Name,
                                           ClangTidyContext *Context)
    : TransformerClangTidyCheck(Name, Context) {
  setRule(applyFirst({gb2ib, inputs_convert}));
}

// void ExpanderConvertCheck::registerMatchers(MatchFinder * Finder) {
//   // FIXME: Add matchers.
//   Finder->addMatcher(functionDecl().bind("x"), this);
// }

// void ExpanderConvertCheck::check(const MatchFinder::MatchResult &Result) {
//   // FIXME: Add callback implementation.
//   const auto *MatchedDecl = Result.Nodes.getNodeAs<FunctionDecl>("x");
//   if (!MatchedDecl->getIdentifier() ||
//       MatchedDecl->getName().startswith("awesome_"))
//     return;
//   diag(MatchedDecl->getLocation(), "function %0 is insufficiently awesome")
//       << MatchedDecl
//       << FixItHint::CreateInsertion(MatchedDecl->getLocation(), "awesome_");
//   diag(MatchedDecl->getLocation(), "insert 'awesome'", DiagnosticIDs::Note);
// }

} // namespace clang::tidy::misc
