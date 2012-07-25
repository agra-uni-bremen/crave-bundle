EX = ex1_seed_dist  ex2_constr_ref  ex3_inh_soft_next  ex4_constr_mng  ex5_vec_constr  ex6_inline_gen

all:
	for dir in $(EX); do \
		cd $${dir} && make && cd .. ; \
	done ;

clean:
	for dir in $(EX); do \
		cd $${dir} && make clean && cd .. ; \
	done ;
