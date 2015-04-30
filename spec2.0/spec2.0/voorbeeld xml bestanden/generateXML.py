import sys, getopt, csv
import bs4, re
from bs4 import BeautifulSoup

orig_prettify = bs4.BeautifulSoup.prettify
r = re.compile(r'^(\s*)', re.MULTILINE)
def prettify(self, encoding=None, formatter="minimal", indent_width=4):
    return r.sub(r'\1' * indent_width, orig_prettify(self, encoding, formatter))
bs4.BeautifulSoup.prettify = prettify

def createWallOn(soup, veldTag, x, y):
    print "Creating Wall at (" + str(x) + "," + str(y) + ")"
    #<MUUR beweegbaar="false" x="0" y="0" />
    obstacleTag = soup.new_tag("MUUR")
    obstacleTag['beweegbaar'] = 'false'
    obstacleTag['x'] = x
    obstacleTag['y'] = y
    veldTag.append(obstacleTag)

def createGateOn(soup, veldTag, x, y, id):
    print "Creating Gate at (" + str(x) + "," + str(y) + ")"
    #<POORT beweegbaar="false" x="0" y="0">
    #   <ID>gateid</ID>
    #</POORT>
    obstacleTag = soup.new_tag("POORT")
    obstacleTag['beweegbaar'] = 'false'
    obstacleTag['x'] = x
    obstacleTag['y'] = y
    idTag = soup.new_tag("ID")
    idTag.string = id
    obstacleTag.append(idTag)
    veldTag.append(obstacleTag)

def createGoalOn(soup, veldTag, x, y):
    print "Creating Goal at (" + str(x) + "," + str(y) + ")"
    #<DOEL x="0" y="0" />
    goalTag = soup.new_tag("DOEL")
    goalTag['x'] = x
    goalTag['y'] = y
    veldTag.append(goalTag)

def createPlayerOn(soup, veldTag, x, y):
    print "Creating Player at (" + str(x) + "," + str(y) + ")"
    #<SPELER x="4" y="5" /> --- FILL in coords HERE!!
    speler = soup.find_all('SPELER')[0]
    speler['x'] = x
    speler['y'] = y

def createButtonOn(soup, veldTag, x, y, id):
    print "Creating Button at (" + str(x) + "," + str(y) + ")"
    #<KNOP x="3" y=5" gateid="gateid" />
    buttonTag = soup.new_tag("KNOP")
    buttonTag['x'] = x
    buttonTag['y'] = y
    buttonTag['id'] = id
    veldTag.append(buttonTag)

def createBarrelOn(soup, veldTag, x, y):
    print "Creating Barrel at (" + str(x) + "," + str(y) + ")"
    #<TON beweegbaar="true" x="3" y="4" />
    obstacleTag = soup.new_tag("TON")
    obstacleTag['beweegbaar'] = 'true'
    obstacleTag['x'] = x
    obstacleTag['y'] = y
    veldTag.append(obstacleTag)

def createWaterOn(soup, veldTag, x, y):
    print "Creating Water at (" + str(x) + "," + str(y) + ")"
    #<WATER beweegbaar="false" x="3" y="4" />
    obstacleTag = soup.new_tag("WATER")
    obstacleTag['beweegbaar'] = 'false'
    obstacleTag['x'] = x
    obstacleTag['y'] = y
    veldTag.append(obstacleTag)

def createMonsterOn(soup, veldTag, x, y, id):
    print "Creating Monster at (" + str(x) + "," + str(y) + ")"
    #<MONSTER x="3" y="4" />
    obstacleTag = soup.new_tag("MONSTER")
    obstacleTag['x'] = x
    obstacleTag['y'] = y
    idTag = soup.new_tag("ID")
    idTag.string = id
    obstacleTag.append(idTag)
    veldTag.append(obstacleTag)

def createBoobyTrapOn(soup, veldTag, x, y):
    print "Creating Monster at (" + str(x) + "," + str(y) + ")"
    #<VALSTRIK x="3" y="4" />
    obstacleTag = soup.new_tag("VALSTRIK")
    obstacleTag['x'] = x
    obstacleTag['y'] = y
    veldTag.append(obstacleTag)


def createCellOn(soup, veldTag, cell, x, y):
    if cell == 'W':
        createWallOn(soup, veldTag, x, y)
    elif cell[0] == '_':
        createGateOn(soup, veldTag, x, y, cell[1:len(cell)])
    elif cell == 'X':
        createGoalOn(soup, veldTag, x, y)
    elif cell == 'Y':
        createPlayerOn(soup, veldTag, x, y)
    elif cell[0] == '.':
        createButtonOn(soup, veldTag, x, y, cell[1:len(cell)])
    elif cell == 'O':
        createBarrelOn(soup, veldTag, x, y)
    elif cell == '~':
        createWaterOn(soup, veldTag, x, y)
    elif cell[0] == 'M':
        createMonsterOn(soup, veldTag, x, y, cell[1:len(cell)])
    elif cell == '#':
        createBoobyTrapOn(soup, veldTag, x, y)

def main(argv):
    inputfile = ''
    try:
        opts, args = getopt.getopt(argv,"hi:",["ifile="])
    except getopt.GetoptError:
        print('generateXML.py -i <inputfile>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('generateXML.py -i <inputfile>')
            sys.exit()
        elif opt in ("-i", "--ifile"):
            inputfile = arg

    with open(inputfile, 'rb') as csvfile:
        soup = BeautifulSoup('', 'xml')
        
        veldTag = soup.new_tag("VELD")
        soup.append(veldTag)
        
        csvreader = csv.reader(csvfile, delimiter=',')
        Levelname = ''
        Playername = ''
        height = 0
        width = 0

        for y, row in enumerate(csvreader):
            if row[0] == "levelname":
                #<NAAM>Level 1</NAAM>
                Levelname =  row[1]
                print "Creating Level: " + Levelname
                nameTag = soup.new_tag("NAAM")
                nameTag.string = Levelname
                veldTag.append(nameTag)
            elif row[0] == "playername":
                #<SPELER x="4" y="5"> ---> FILL in coords at later time!!
                #    <NAAM>Chip</NAAM>
                #</SPELER>
                Playername = row[1]
                print "Creating Player: " + Playername
                playerTag = soup.new_tag("SPELER")
                veldTag.append(playerTag)
                
                playerNameTag = soup.new_tag("NAAM")
                playerNameTag.string = Playername
                playerTag.append(playerNameTag)
            elif row[0] == "width":
                #<BREEDTE>10</BREEDTE>
                width = row[1]
                print "LevelWidth = " + str(width)
                widthtag = soup.new_tag("BREEDTE")
                widthtag.string = width
                veldTag.append(widthtag)
            elif row[0] == "height":
                #<LENGTE>10</LENGTE>
                height = row[1]
                print "LevelHeight = " + str(height)
                heighttag = soup.new_tag("LENGTE")
                heighttag.string = height
                veldTag.append(heighttag)
            else:
                for x, cell in enumerate(row):
                    createCellOn(soup, veldTag, cell, x, int(height) - 1 - (y - 4) )  #inverting Y dimension!!!

        file = open(inputfile + '.xml', 'w')
        file.write(soup.prettify(indent_width=4))

if __name__ == "__main__":
    main(sys.argv[1:])