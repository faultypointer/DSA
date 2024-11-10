import sys
import math
import re

def print_help():
    print("Usage: doc-dist.py <file1> <file2>")

def count_freq(vec, text):
    words = re.findall("\w+", text)
    print("total no of words: ", len(words))
    distinct_words = 0
    for word in words:
        word = word.lower()
        if word in vec:
            vec[word] += 1
        else:
            vec[word] = 1
            distinct_words += 1
    print("Distinct words: ", distinct_words)

def dot_product(vec1, vec2):
    res = 0.0
    for word in vec1:
        if word in vec2:
            res += vec1[word] * vec2[word]
    return res

def cosine_distance(vec1, vec2):
    dot = dot_product(vec1, vec2)
    print("dot: ", dot)
    normalized_len = math.sqrt(dot_product(vec1, vec1) * dot_product(vec2, vec2))
    return math.acos(dot / normalized_len)

def main():
    if (len(sys.argv) != 3):
        print_help()
        return
    doc1 = ""
    doc2 = ""
    vec1 = {}
    len1 = 0
    vec2 = {}
    len2 = 0
    with open(sys.argv[1], "r") as f:
        doc1 = f.read()
    with open(sys.argv[2], "r") as f:
        doc2 = f.read()
    
    count_freq(vec1, doc1)
    count_freq(vec2, doc2)
    print("Cosine Distance: ", cosine_distance(vec1, vec2))


if __name__ == "__main__":
    # import profile
    # profile.run("main()")
    main()
