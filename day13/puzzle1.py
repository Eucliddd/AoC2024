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
            "c": int(match[4]),
            "d": int(match[1]),
            "e": int(match[3]),
            "f": int(match[5])
        }
        for match in matches
    ]

    return results

def solve(equations):
    res = 0
    for eq in equations:
        x, y = symbols("x y")
        eq1 = Eq(eq["a"] * x + eq["b"] * y, eq["c"])
        eq2 = Eq(eq["d"] * x + eq["e"] * y, eq["f"])
        sol = sympy.solve((eq1, eq2), (x, y))
        if sol[x] < 0 or sol[y] < 0:
            continue
        if sol[x] % 1 != 0 or sol[y] % 1 != 0:
            continue
        res += 3 * sol[x] + sol[y]
    return res

if __name__ == "__main__":
    equations = read_input("input.txt")
    print(solve(equations))