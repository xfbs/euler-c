import sys

header_file = sys.argv[1]
code_file = sys.argv[2]
numbers = sys.argv[3::]

sys.stdout = open(code_file, 'w')

print("#include \"euler.h\"")

#for num in numbers:
#    num = "%03d" % int(num, 10)
#    print("#include \"solve/solve{}.h\"".format(num))

print("#include \"{}\"".format(header_file))

print()
print("const struct euler_problem *euler_problems[] = {")

for num in numbers:
    num = "%03d" % int(num, 10)
    print("    &problem{},".format(num))

print("    NULL,")
print("};")

sys.stdout = open(header_file, 'w')

print("#include \"euler.h\"")
print()
for num in numbers:
    num = "%03d" % int(num, 10)
    print("extern const struct euler_problem problem{};".format(num))
