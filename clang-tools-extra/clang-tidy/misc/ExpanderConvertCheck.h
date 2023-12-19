//===--- ExpanderConvertCheck.h - clang-tidy --------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_EXPANDERCONVERTCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_EXPANDERCONVERTCHECK_H

#include "../ClangTidyCheck.h"
#include "../utils/TransformerClangTidyCheck.h"
namespace clang::tidy::misc {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/misc/expander-convert.html
class ExpanderConvertCheck : public  utils::TransformerClangTidyCheck{
public:
  ExpanderConvertCheck(StringRef Name, ClangTidyContext *Context);
  // void storeOptions(ClangTidyOptions::OptionMap &Opts) override;

private:
  const std::vector<StringRef> StringLikeClassesOption;
  const StringRef AbseilStringsMatchHeaderOption;
};

} // namespace clang::tidy::misc

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_MISC_EXPANDERCONVERTCHECK_H
