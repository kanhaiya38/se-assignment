import re
import sys


def parseLine(text):
    pat = re.compile(
        r'<?text start="(\d+\.\d+)" dur="(\d+\.\d+)">(.*)</text>?')
    m = re.match(pat, text)
    if m:
        return (m.group(1), m.group(2), m.group(3))
    else:
        return None


def formatSrtTime(secTime):
    sec, micro = str(secTime).split('.')
    m, s = divmod(int(sec), 60)
    h, m = divmod(m, 60)
    return "{:02}:{:02}:{:02},{}".format(h, m, s, micro)


def printSrtLine(i, elms):
    return "{}\n{} --> {}\n{}\n\n".format(i, formatSrtTime(elms[0]), formatSrtTime(float(elms[0])+float(elms[1])), elms[2])


def main():
    fileName = sys.argv[1]
    with open(fileName, 'r') as infile:
        # get all lines in buffer
        buf = []
        for line in infile:
            buf.append(line.rstrip('\n'))

    # Split the buffer to get one string per tag.
    buf = "".join(buf).split('><')

    i = 1
    srtfileName = fileName.replace('.xml', '.srt')
    with open(srtfileName, 'w') as outfile:
        # write into srt file
        for text in buf:
            parsed = parseLine(text)
            if parsed:
                outfile.write(printSrtLine(i, parsed))
                i += 1
    print('{} converted to srt'.format(srtfileName))


if __name__ == "__main__":
    main()

