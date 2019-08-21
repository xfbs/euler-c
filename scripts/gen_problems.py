import sys

out_file = sys.argv[1]
numbers = sys.argv[2::]

sys.stdout = open(out_file, 'w')

print("#include \"euler.h\"")

for num in numbers:
    num = "%03d" % int(num, 10)
    print("#include \"solve/solve{}.h\"".format(num))

print()
print("const struct euler_problem *euler_problems[] = {")

for num in numbers:
    num = "%03d" % int(num, 10)
    print("    &problem{},".format(num))

print("    NULL,")
print("};")
