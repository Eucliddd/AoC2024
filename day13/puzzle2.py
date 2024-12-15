from sympy import symbols, Eq
import sympy
import regex as re
def read_input(str):
    with open(str, "r") as f:
        pattern = r"""
            Button\sA:\sX\+(\d+),\sY\+(\d+)\n
            Button\sB:\sX\+(\d+),\sY\+(\d+)\n
            Prize:\sX=(\d+),\sY=(\d+)
        """
        lines = f.read()
        matches = re.findall(pattern, lines, re.VERBOSE)
        results = [
        {
            "a": int(match[0]),
            "b": int(match[2]),
            "c": 10000000000000 + int(match[4]),
            "d": int(match[1]),
            "e": int(match[3]),
            "f": 10000000000000 + int(match[5])
        }
        for match in matches
    ]

    return results

def solve(equations):
    res = 0
    for eq in equations:
        #print(eq)
        a, b, c, d, e, f = eq["a"], eq["b"], eq["c"], eq["d"], eq["e"], eq["f"]
        numerator = d * c - a * f
        denominator = d * b - a * e
        if denominator == 0:
            continue
        if numerator % denominator != 0:
            continue
        y = numerator // denominator
        if y < 0:
            continue
        #print(y)
        numerator = c - b * y
        denominator = a
        if denominator == 0:
            continue
        if numerator % denominator != 0:
            continue
        x = numerator // denominator
        #print(x)
        if x < 0:
            continue
        res += 3 * x + y
    return res

if __name__ == "__main__":
    equations = read_input("input.txt")
    print(solve(equations))