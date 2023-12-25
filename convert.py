import shutil
import os
import argparse

parser = argparse.ArgumentParser(description="Process some integers.")
parser.add_argument("op", help="the name of operation to convert")
args = parser.parse_args()
op = args.op

base_path = ""
graph_kernel_path = base_path +  "/mindspore/ccsrc/backend/common/graph_kernel"
compile_commands_path = base_path + "/build/mindspore"  # path to compile_commands.json
expanders_path = graph_kernel_path + "/expanders/"
op_filename = op + ".cc"
op_bak_filename = op+"_bak.cc"

if __name__ == "__main__":
    shutil.copyfile(expanders_path + op_filename, expanders_path + op_bak_filename)

    os.system('clang-tidy -p ' + compile_commands_path + ' ./sigmoid.cc -checks="-*,misc-expander-*" --fix-errors')

    