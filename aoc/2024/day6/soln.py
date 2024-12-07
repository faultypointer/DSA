dir = {
    'up': (-1, 0),
    'down': (1, 0),
    'right': (0, 1),
    'left': (0, -1)
}

rotate_right = {
    'up': 'right',
    'down': 'left',
    'right': 'down',
    'left': 'up'
}

def print_gird(grid):
    for row in grid:
        for cell in row:
            print(cell, end = ' ')
        print()

def within_grid(pos, rows,  cols):
    if (pos[0] < 0 or pos[1] < 0 or
        pos[0] >= rows or pos[1] >= cols):
        return False
    return True
def part_one():
    with open("input.txt", "r") as f:
        content = f.read()
        gird = []
        guard_pos = (-1, -1)
        guard_dir = 'up'
        visited = set()
        for i, line in enumerate(content.strip().split('\n')):
            row = []
            for j, char in enumerate(line):
                match char:
                    case '.':
                        row.append(0)
                    case '#':
                        row.append(1)
                    case '^':
                        row.append(0)
                        guard_pos = (i, j)
            gird.append(row)

        # print_gird(gird)
        
        while (within_grid(guard_pos, len(gird), len(gird[0]))):
            visited.add(guard_pos)
            # print("pos: ", guard_pos, "dir: ", guard_dir)
            new_pos = guard_pos[0] + dir[guard_dir][0], guard_pos[1] + dir[guard_dir][1]
            if within_grid(new_pos, len(gird), len(gird[0])):
                # print("new_pos: ", new_pos, "rows: ", len(gird), "cols: ", len(gird[0]))
                # print("actual row: ", gird[new_pos[0]])
                if gird[new_pos[0]][new_pos[1]] == 1:
                    guard_dir = rotate_right[guard_dir]
                    continue
            guard_pos = new_pos

        print("Distinct Position visited: ", len(visited))


def part_two():
    with open("test.txt", "r") as f:
        content = f.read()
        gird = []
        guard_pos = (-1, -1)
        guard_dir = 'up'
        visited = set()
        obstacles = []
        for i, line in enumerate(content.strip().split('\n')):
            row = []
            for j, char in enumerate(line):
                match char:
                    case '.':
                        row.append(0)
                    case '#':
                        row.append(1)
                        obstacles.append((i, j))
                    case '^':
                        row.append(0)
                        guard_pos = (i, j)
            gird.append(row)

        for i in range(len(obstacles)):
            curr = obstacles[i]
            possible_loop = set()
            possible_loop.add(curr)
            for j in range(i+1, len(obstacles)):
                second = obstacles[j]
                if curr[0] + 1 == second[0]:
                    possible_loop.add(second)
                    for j in range(i, len(obstacles)):
                        third = obstacles[j]
                        # print(f"first: {curr}, second: {second}, third: {third}")
                        if third[1] == second[1] - 1 or third[1] == curr[1] - 1:
                            possible_loop.add(third)
                elif curr[1] - 1 == second[1]:
                    possible_loop.add(second)
                    for j in range(i, len(obstacles)):
                        third = obstacles[j]
                        # print(f"first: {curr}, second: {second}, third: {third}")
                        if third[0] == second[0] + 1:
                            possible_loop.add(third)
            print(possible_loop)

        print(obstacles)


if __name__ == "__main__":
    part_two()
                        

