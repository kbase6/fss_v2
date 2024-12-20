import json 
import sys
import subprocess
import os

def parse_json(json_str):
    """
    Parse the JSON string into a Python dictionary
    """
    try:
        data = json.loads(json_str)
        return data
    except json.JSONDecodeError as e:
        print("Invalid JSON format:", e)
        return None
    
def is_numeric(value):
    """
    Check if the given string value represents a numeric literal
    """
    try:
        float(value)
        return True
    except ValueError:
        return False
    
def generate_cpp_prefix():
    includes = [
        '<iostream>',
        '<functional>',
        '<map>',
        '<string>',
        '<vector>',
        '"../comm/comm.hpp"',
        '"../fss-base/dcf/distributed_comparison_function.hpp"',
        '"../fss-base/ddcf/dual_dcf.hpp"',
        '"../fss-base/dpf/distributed_point_function.hpp"',
        '"../fss-base/prg/prg.hpp"',
        '"../fss-gate/comp/integer_comparison.hpp"',
        '"../fss-gate/fm-index/fss_fmi.hpp"',
        '"../fss-gate/internal/fsskey_io.hpp"',
        '"../fss-gate/rank/fss_rank.hpp"',
        '"../fss-gate/zt/zero_test_dpf.hpp"',
        '"../tools/secret_sharing.hpp"',
        '"../tools/tools.hpp"',
        '"../utils/file_io.hpp"',
        '"../utils/utils.hpp"'
        ]
    
    prefix = ''
    for item in includes:
        prefix += '#include ' + item + '\n' 
    
    prefix += '\n'
    return prefix
    
def generate_cpp_main(functions):
    """
    Generate main function of the C++ code and return the final computed value
    """
    cpp_main = "int main() {\n"
    
    # Dictionary to keep track fo variable declarations
    variables = {}
    
    # List to keep track of the order of function executions
    execution_order = []
    
    for func in functions:
        name = func['name']
        func_name = func['function']
        params = func['parameters']
        
        resolved_params = []
        for key in sorted(params.keys()):
            param = params[key]
            if param in variables:
                resolved_params.append(param)
            elif is_numeric(param):
                resolved_params.append(param)
            else:
                resolved_params.append(param) # Assume it is a variable defined elsewhere

        # Create the variable declaration line
        param_str = ", ".join(resolved_params)
        cpp_main += f"    auto {name} = {func_name}({param_str});\n"
        variables[name] = True  # Mark this variable as defined
        execution_order.append(name)  # Track execution order

    # Ensure there is at least one function to return
    if execution_order:
        final_var = execution_order[-1]
        cpp_main += f"    return {final_var};\n"
    else:
        cpp_main += "    return 0;\n"  # Default return if no functions are defined

    cpp_main += "}\n"
    return cpp_main

def generate_code(json_data):
    """
    Generate the complete C++ code based on the parsed JSON data
    """
    functions = json_data.get('functions', [])
    
    cpp_prefix = generate_cpp_prefix()
    cpp_main = generate_cpp_main(functions)
    
    cpp_code = (
        f'{cpp_prefix}'
        f'{cpp_main}'
    )
    
    return cpp_code

def compile_code(source_file, output_file):
    if not os.path.exists(source_file):
        sys.exit(1)
    
    compile_cmd = ["g++", "-02", source_file, "-o", output_file]
    compile_proc = subprocess.run(compile_cmd, capture_output = True, text = True)
    
    if compile_proc.returncode != 0:
        print(compile_proc.stderr)
        sys.exit(1)
        
    run_proc = subprocess.run([f"./{output_file}"], capture_output=True, text=True)
    if run_proc.returncode != 0:
        print(run_proc.stderr)
    else:
        print(run_proc.stdout)

def compiler(json_input):
    data = parse_json(json_input)
    if not data:
        return
    
    cpp_code = generate_code(data)
    
    with open("generated_code.cpp", "w") as file:
        file.write(cpp_code)
        

if __name__ == "__main__":
    example_json = """
    {
        "functions": [
            {
                "name": "func1",
                "function": "add",
                "parameters": {
                    "x1": "10",
                    "x2": "3"
                }
            },
            {
                "name": "func2",
                "function": "mult",
                "parameters": {
                    "x1": "func1",
                    "x2": "10"
                }
            }
        ]
    }
    """
    compiler(example_json)
