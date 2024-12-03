import re

def part_one():
    with open("input.txt", "r") as f:
        result = 0
        content = f.read()
        matches = re.findall("mul\(([0-9]{1,3}),([0-9]{1,3})\)", content)
        for uncorrupted in matches:
            a, b = int(uncorrupted[0]), int(uncorrupted[1])
            result += a*b
        print("sum: ", result)


def part_two():
    with open("input.txt", "r") as f:
        result = 0
        do = True
        content = f.read()
        for i in range(len(content)):
            if content[i] == 'd':
                if i+4 < len(content) and content[i:i+4] == "do()":
                    print("do at: ", i)
                    do = True
                    i += 3
                elif i+7 < len(content) and content[i:i+7] == "don't()":
                    print("don't at: ", i)
                    do = False
                    i += 7
            elif do and i+4 < len(content) and content[i:i+4] == "mul(":
                maatch = re.search("mul\(([0-9]{1,3}),([0-9]{1,3})\)", content[i:i+12])
                if maatch == None:
                    continue
                print("mul at: ", i)
                a, b = maatch.group(1), maatch.group(2)
                a, b = int(a), int(b)
                result += a * b
                i += 8
        print("sum part two: ", result)





if __name__ == "__main__":
    part_two()
