%No node contains links to itself
%Node 1 contains links to all of the other nodes
%Node 2 contains links to node 1 and node 4
%Node 3 contains no links
%Node 4 contains links to nodes 1, 2, and 3
%Node 5 contains links to nodes 2 and 4.

ConnectivityMatrix = [0 1 1 1 1;1 0 0 1 0;0 0 0 0 0;1 1 1 0 0;0 1 0 1 0];
[rows, columns] = size(ConnectivityMatrix);
dimension = size(ConnectivityMatrix, 1);
columnsums = sum(ConnectivityMatrix, 1);

%Random walk probability factor
p = 0.85;

%Generate stochastic matrix
zerocolumns = find(columnsums~=0);
D = sparse( zerocolumns, zerocolumns, 1./columnsums(zerocolumns), dimension, dimension);
StochasticMatrix = ConnectivityMatrix * D;
[row, column] = find(columnsums==0);
StochasticMatrix(:, column) = 1./dimension;

%Generate transition matrix
Q = ones(dimension, dimension);
TransitionMatrix = p * StochasticMatrix + (1 - p) * (Q/dimension);

%PageRank
PageRank = ones(dimension, 1);
for i = 1:100 PageRank = TransitionMatrix * PageRank; end
PageRank = PageRank / sum(PageRank);

