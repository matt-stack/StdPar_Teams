all: 2_stdpar_teams_abstract.cpp
	nvc++ -stdpar=gpu -gpu=cc70 --std=c++20 ./2_stdpar_teams_abstract.cpp
