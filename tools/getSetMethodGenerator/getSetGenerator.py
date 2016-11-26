import re

#------------------------------------------------------------------------------
def extractClassName():
    className = 'Unknown'

    f = open( 'input.txt', 'r' )
    if (f):
        content = f.read()
        pattern = re.compile( '(className:) (.*)' )
        matches = pattern.findall(content)

        if len(matches) == 1:
            className = matches[0][1]
    return className

#------------------------------------------------------------------------------
def extractMembers():

    results = []
    f = open( 'input.txt', 'r' )
    if (f):
        content = f.read()
        rePattern = re.compile('(.*) (.*)(;)(.*\/\/.*|)') # 4 groupes... (type) (nomDeVariable) (;) (commentaire) 
        matches = rePattern.findall(content)

        for m in matches:
            #the input assume there is a 'm' in front of every memberVariable name..
            #lets remove it.
            capitalizedMember = m[1][1:]
            results.append( (m[0], capitalizedMember, m[3]) ) # ('type', 'nomDeLaVariable', 'commentaire')
        f.close()
    return results

#------------------------------------------------------------------------------
def generateMembers( extractedMembers ):
    results = []

    for m in extractedMembers:
        results.append( '%s m%s;%s' % ( m[0], m[1], m[2] ) )

    return results

#------------------------------------------------------------------------------
def generateGettersDefinition( members ):
    results = []

    for m in members:
        method = '%s get%s() const;' % ( m[0], m[1] )
        results.append( method )

    return results

#------------------------------------------------------------------------------
def generateGettersInstantiation( className, members ):
    results = []

    for m in members:
        instantionation = '//------------------------------------------------------------------------------\n'
        instantionation += '%s %s::get%s() const\n' % ( m[0], className, m[1] )
        instantionation += '{ return m%s; }\n' % m[1]
        results.append( instantionation )

    return results

#------------------------------------------------------------------------------
def generateSettersDefinition( members ):
    results = []

    for m in members:
        method = 'void set%s(%s);' % (m[1], m[0])
        results.append( method )

    return results

#------------------------------------------------------------------------------
def generateSettersInstantiation( className, members ):
    results = []

    for m in members:
        instantionation = '//------------------------------------------------------------------------------\n'
        instantionation += 'void %s::set%s(%s)\n' % ( className, m[1], m[0] )
        instantionation += '{}\n'
        results.append( instantionation )

    return results

#------------------------------------------------------------------------------
def toString( arrayOfStrings ):
    r = ''
    for i in arrayOfStrings:
        r += '%s\n' % i
    return r

#------------------------------------------------------------------------------
print 'Generating methods'

className = extractClassName()
extractedMembers = extractMembers() #tuple sous forme ( 'type', 'nomDuMembre', 'commentaire' )



members = generateMembers( extractedMembers )
#sort the tuples by variable name so the functions
#get out in alphabetical sort
sortedMembers = extractedMembers
#sort result by function name
sortedMembers.sort(key=lambda x: x[1])

gettersDefinition = generateGettersDefinition( sortedMembers )
settersDefinition = generateSettersDefinition( sortedMembers )

gettersInstantiation = generateGettersInstantiation( className, sortedMembers )
setterInstantiation = generateSettersInstantiation( className, sortedMembers )

print toString(members)
print toString(gettersDefinition)
print toString(settersDefinition)
print toString(gettersInstantiation)
print toString(setterInstantiation)

f = open('output.txt', 'w+')
if(f):
    content = '''
    Members\n%s

    Getters\n%s

    Setters\n%s

    Getter instantiation\n%s

    Setter instantiation\n%s
    ''' % ( toString(members), 
      toString(gettersDefinition),
      toString(settersDefinition),
      toString(gettersInstantiation),
      toString(setterInstantiation) )

    f.write( content )

    f.close()

print 'Outputed in output.txt'
