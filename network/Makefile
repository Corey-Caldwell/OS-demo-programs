targets = gethost gethost-fancy ispeak ilisten iecho ilisten2 time37 qotd

.PHONY: all
all: $(targets)

ilisten2: ilisten2.C
	$(CXX) $(CXXFLAGS) ilisten2.C -o ilisten2 -lpthread

.PHONY: clean
clean:
	rm -f $(targets)
