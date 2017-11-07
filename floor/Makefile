CXX= g++-5
CXXFLAGS= -std=c++17 -MMD -g
OBJECT=main.o object.o floor.o rulesout.o ../control/attack_rules.o chamber.o ../item/potion.o ../item/treasure.o ../item/item.o ../character/races.o ../character/character.o
DEPEND=${OBJECT:.o=.d}
EXEC = cc3k

a.out: ${OBJECT}
	${CXX} ${CXXFLAGS} ${OBJECT} -o ${EXEC}

-include ${DEPEND}

clean:
	rm -f *.o *.d