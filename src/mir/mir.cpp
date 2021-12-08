// SPDX-license-identifier: Apache-2.0
// Copyright © 2021 Intel Corporation

#include "mir.hpp"
#include "exceptions.hpp"

namespace MIR {

BasicBlock::BasicBlock() : instructions{}, next{std::monostate{}}, parents{} {};

BasicBlock::BasicBlock(std::unique_ptr<Condition> && con)
    : instructions{}, next{std::move(con)}, parents{} {};

Condition::Condition(Object && o)
    : condition{std::move(o)}, if_true{std::make_shared<BasicBlock>()}, if_false{nullptr} {};

Condition::Condition(Object && o, std::shared_ptr<BasicBlock> s)
    : condition{std::move(o)}, if_true{s}, if_false{nullptr} {};

const Object Compiler::get_id(const std::vector<Object> & args,
                              const std::unordered_map<std::string, Object> & kwargs) const {
    if (!args.empty()) {
        throw Util::Exceptions::InvalidArguments(
            "compiler.get_id(): takes no positional arguments");
    }
    if (!kwargs.empty()) {
        throw Util::Exceptions::InvalidArguments("compiler.get_id(): takes no keyword arguments");
    }

    return std::make_unique<String>(toolchain->compiler->id());
};

Variable::operator bool() const { return !name.empty(); };

} // namespace MIR
