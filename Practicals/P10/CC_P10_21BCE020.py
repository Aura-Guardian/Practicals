class Optimizer:
    def __init__(self, code):
        self.code = code
        self.constants = {} 

    def constant_folding(self):
        optimized_code = []
        for line in self.code:
            if "=" in line and ";" in line:
                parts = line.split("=")
                lhs = parts[0].strip().replace("int ", "") 
                rhs = parts[1].strip().replace(";", "")

                if rhs.isdigit():
                    self.constants[lhs] = int(rhs)
                    optimized_code.append(line)
                # If RHS is an expression, check if it can be folded
                elif "+" in rhs:
                    operands = rhs.split("+")
                    left_operand = operands[0].strip()
                    right_operand = operands[1].strip()

                    # Check if operands are constants
                    if left_operand.isdigit() and right_operand.isdigit():
                        const_sum = int(left_operand) + int(right_operand)
                        optimized_code.append(f"{lhs} = {const_sum};")
                        self.constants[lhs] = const_sum
                    elif left_operand in self.constants and right_operand in self.constants:
                        const_sum = self.constants[left_operand] + self.constants[right_operand]
                        optimized_code.append(f"{lhs} = {const_sum};")
                        self.constants[lhs] = const_sum
                    else:
                        optimized_code.append(line)  # keep as is if not foldable
                else:
                    optimized_code.append(line)  # keep as is for non-constant assignments
            else:
                optimized_code.append(line)  # keep other lines (e.g., printf) as is

        self.code = optimized_code

    def get_code(self):
        return "\n".join(self.code)

source_code = [
    "int a = 10;",
    "int b = 20;",
    "int c = a + b;",
    "printf(\"Sum is: %d\\n\", c);"
]

optimizer = Optimizer(source_code)
optimizer.constant_folding()
print("Optimized Code:")
print(optimizer.get_code())
