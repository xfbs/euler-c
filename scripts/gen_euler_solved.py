import sys

out_file = sys.argv[1]
number_str = sys.argv[2]
description_file = sys.argv[3]
solution_file = sys.argv[4]

sys.stdout = open(out_file, 'w')

number = int(number_str, 10)
cwnumber = "%03d" % (number)

title = " ".join(open(description_file, "r").readline().rstrip().split()[3::])
solution = open(solution_file, "r").read()

print("#include \"euler.h\"")
print("#include \"solve/solve{}.h\"".format(cwnumber))
print()

print("const struct euler_problem problem{} = {{".format(cwnumber))
print("    .number = {},".format(number))
print("    .name = \"{}\",".format(title))
print("    .hash = \"{}\",".format(solution))
print("    .solve = solve{},".format(cwnumber))
print("    .input = input{},".format(cwnumber))
print("};")
