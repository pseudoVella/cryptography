CXX = g++
CXXFLAGS = -Wall -v
AR = ar
ARFLAGS = rvs
MAKE = make
dirs := sha-256 hmac-sha256 large_Ints large_float
vcrypt_files := sha.o hmacsha256.o uint1024_t.o ufp_t.o
vcrypt_targets = $(addprefix $(out)/, $(vcrypt_files))
samp_files = shaex hmacex hmacCTR 1024test ufptest
samp_targets = $(addprefix bin/, $(samp_files))
out := lib

INCLUDE = $(addprefix -I, $(dirs))

.PHONY: all
all: $(out)/libvcrypt.a

$(out)/libvcrypt.a: $(vcrypt_targets)
	cd $(out) && $(AR) $(ARFLAGS) $(@F) $(?F)

#implicit rule for compiling vcrypt_targets
$(out)/%.o: CXXFLAGS += -O2 -c -fPIC
$(out)/%.o: */%.cpp */%.h
	if [ ! -d $(out) ]; then mkdir $(out); fi
	$(CXX) $(CXXFLAGS) -o $@ $< $(INCLUDE)

#additional explicit prerequesites for individual vcrypt_targets
$(out)/hmacsha256.o: $(out)/sha.o

.PHONY: sample
sample: $(samp_targets)

bin/%: */sample/%.cpp
	if [ ! -d bin ]; then mkdir bin; fi
	$(CXX) $(CXXFLAGS) -o $@ $< $(INCLUDE) -L$(out) -lvcrypt
bin/1024test: $(out)/uint1024_t.o
bin/ufptest: $(out)/libvcrypt.a

.PHONY: clean
clean:
	if [ -d $(out) ]; then rm -rf $(out)/*.o; fi

.PHONY: dist-clean
dist-clean:
	if [ -d $(out) ]; then rm -rf $(out); fi
	if [ -d bin ]; then rm -rf bin; fi
