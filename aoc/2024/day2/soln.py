def part_one():
    with open("input.txt", "r") as f:
        safe_count = 0
        for line in f.read().splitlines():
            num_count = 0
            change = 0
            prev = 0
            is_safe = True
            for num_str in line.split():
                num = int(num_str)
                num_count += 1
                if num_count == 1:
                    prev = num
                    continue
                elif num_count == 2:
                    change = prev - num
                else:
                    current_change = prev - num
                    if current_change * change < 0:
                        is_safe = False
                        break
                    change = current_change
                if abs(change) < 1 or abs(change) > 3:
                    is_safe = False
                    break
                prev = num
            if is_safe:
                safe_count += 1
        print(f"safe count: {safe_count}")


def is_record_safe(record: list):
    if len(record) < 2:
        return True
    else:
        first = True
        change = 0
        for i in range(len(record) -1):
            a, b = record[i], record[i+1]
            current_change = a-b
            if first:
                first = False
                if abs(current_change) < 1 or abs(current_change) > 3:
                    return False
                change = current_change
            elif change * current_change < 0 or abs(current_change) < 1 or abs(current_change) > 3:
                return False
            change = current_change
    return True



def part_two():
    with open("input.txt", "r") as f:
        safe_count = 0
        for (i, line) in enumerate(f.read().splitlines()):
            report = [int(num_str) for num_str in line.split()]
            # num_count = 0
            is_safe = False
            # prev = 0
            for i in range(len(report)):
                report_copy = report.copy()
                report_copy.pop(i)
                if is_record_safe(report_copy):
                    is_safe = True
                    break
            if is_safe:
                safe_count += 1
        print(f"safe count after dampner: {safe_count}")


if __name__ == "__main__":
    part_two()
