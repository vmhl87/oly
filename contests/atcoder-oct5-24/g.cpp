/*
 * firstly turn into directed graph: each string {c1 c2}
 * corresponds to an edge from c1 -> c2
 *
 * then notice that we wish to find the minimum directed
 * path covering of this
 *
 * I claim that this is congruent to the DAG obtained by
 * collapsing all cycles to single nodes, and furthermore
 * that solving the problem on this DAG is easier
 */
