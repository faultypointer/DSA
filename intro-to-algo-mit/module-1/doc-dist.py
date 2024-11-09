import sys
import math

def print_help():
    print("Usage: doc-dist.py <file1> <file2>")


def main():
    if (len(sys.argv) != 3):
        print_help()
        return
    doc1 = ""
    doc2 = ""
    docvec1 = {}
    docveclen1 = 0
    docvec2 = {}
    docveclen2 = 0
    with open(sys.argv[1], "r") as f:
        doc1 = f.read()
    with open(sys.argv[2], "r") as f:
        doc2 = f.read()

    for word in doc1.split():
        docvec1[word] = docvec1.get(word, 0) + 1
        docveclen1 += 1
    for word in doc2.split():
        docvec2[word] = docvec2.get(word, 0) + 1
        docveclen2 += 1
    if (docveclen1 * docveclen2 == 0):
        print("one of the document is empty")
        return

    dist = sum(docvec1.get(word) * docvec2.get(word, 0) for word in docvec1) / (docveclen1 * docveclen2)
    print("dist: ", dist)
    print("Arccosice distance of docs: ", math.acos(dist));
if __name__ == "__main__":
    main()
