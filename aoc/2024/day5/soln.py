def put_in_correct_order(update: list, rules: dict):
    previous_pages = []
    for page in update:
        for prev_page in previous_pages:
            if page in rules and prev_page in rules[page]:
                update[update.index(page)], update[update.index(prev_page)] = update[update.index(prev_page)], update[update.index(page)]
                put_in_correct_order(update, rules)
        previous_pages.append(page)



def part_one():
    rules = {}
    generating_rules = True
    summ = 0
    sum_of_corrected = 0
    with open("input.txt", "r") as f:
        content = f.read()
        for line in content.split('\n'):
            if len(line) == 0:
                generating_rules = False
                continue
            if generating_rules:
                rule = [int(x) for x in line.strip().split('|')]
                if rule[0] not in rules:
                    rules[rule[0]] = set([rule[1]])
                else:
                    rules[rule[0]].add(rule[1])
            else:
                update = [int(x) for x in line.strip().split(',')]
                previous_pages = []
                correct_order = True
                for page in update:
                    for prev_page in previous_pages:
                        if page in rules and prev_page in rules[page]:
                            correct_order = False
                            put_in_correct_order(update, rules)
                            break
                    previous_pages.append(page)
                    if not correct_order:
                        break
                if correct_order:
                    summ += update[len(update) // 2]
                else:
                    sum_of_corrected += update[len(update) // 2]
        print("sum: ", summ)
        print("sum_of_corrected: ", sum_of_corrected)


if __name__ == "__main__":
    part_one()
