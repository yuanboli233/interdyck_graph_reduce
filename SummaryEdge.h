#ifndef SUMMARY_EDGE_H
#define SUMMARY_EDGE_H
#include <algorithm>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define MEM_USAGE() {                                  \
    string line; ifstream in("/proc/self/status");     \
    for (unsigned i = 0; i < 16; i++) { getline(in,line); } \
    istringstream inl(line); string x; unsigned mem;        \
    inl >> x >> mem; cout << "mem  = " <<              \
    (double)mem/1024 << "M" << endl; in.close();       \
}

using namespace std;

//inline int TestItemInSet(long *p, unsigned item){
//  //int section  = item / 64;
//  //int offset = item % 64;
//  //unsigned long base  = 1;
//  p = p + item / 64;
//  
//  if (((*p) & (1UL << (item % 64))) == 0)
//    return 0;
//  else
//    return 1;
//}
//
//inline void AddItemToSet(long *p, unsigned item){
//  p = p + item / 64;
//  *p = (*p) | (1UL << (item % 64));
//}
//
///***
// * fast data structure to store summary edges between nodes in graph,
// * summary edges info should only be an unsigned interger.
// */
//class Summaries{
//private:
//    unsigned WordsInSet;
//public:
//    bitmap** summaries;
//    // TODO try vector later
//    bitmap* toIdxOf;
//    bitmap* fromIdxOf;
//
//    Summaries(unsigned vtxNum){
//        bitmap_obstack_initialize(NULL);
//        summaries = new bitmap*[vtxNum];
//        WordsInSet = vtxNum / 64 + 1;
//        toIdxOf = new bitmap[vtxNum];
//        fromIdxOf = new bitmap[vtxNum];
//        for(unsigned i = 0; i < vtxNum; i++){
//            summaries[i] = new bitmap[vtxNum];
//            toIdxOf[i] = BITMAP_ALLOC(NULL);
//            fromIdxOf[i] = BITMAP_ALLOC(NULL);
//        }
//    }
//
//    bool addSummary(unsigned from, unsigned to, unsigned content){
//        if(from == to && content == 0)
//            return true;
//        bool old = false;
//        if(!bitmap_bit_p(toIdxOf[from], to)){
//            summaries[from][to] = BITMAP_ALLOC(NULL);
//            bitmap_set_bit(toIdxOf[from], to);
//            bitmap_set_bit(fromIdxOf[to], from);
//        }
//        old = bitmap_bit_p(summaries[from][to], content);
//        bitmap_set_bit(summaries[from][to], content);
//        return old;
//    }
//
//    bool exists(unsigned from, unsigned to, unsigned amount){
//        if(!bitmap_bit_p(toIdxOf[from], to)){
//            return false;
//        }
//        return bitmap_bit_p(summaries[from][to], amount);
//    }
//} ;

struct NodewithEID{
    unsigned nodeID;
    // edge id is the kind of edges
    unsigned edgeID;
    NodewithEID(unsigned n, unsigned e){
        nodeID = n;
        edgeID = e;
    }
} ;



//struct SummaryCandidate{
//    int from;
//    int to;
//    int amount;
//    /***
//     *  Summary candidate type
//     *  0: Sr
//     *  1: Src
//     *  2: Src_prel
//     *  3: Src_prer
//     *  4: CO
//     */
//    int type;
//
//    SummaryCandidate(int f, int t, int a, int ty){
//        from = f;
//        to = t;
//        amount = a;
//        type = ty;
//    }
//
//    bool operator==(const SummaryCandidate& other) const{
//        return ((from == other.from) && (to == other.to) && (amount == other.amount) && (type == other.type));
//    }
//};
//
//class Worklist{
//    queue<SummaryCandidate> list;
//    unsigned vtxNum;
//public:
//
//    Worklist(unsigned vNum){
//        vtxNum = vNum;
//    }
//
//    unsigned size(){
//        return list.size();
//    }
//    
//    SummaryCandidate front(){
//        return list.front();
//    }
//
//    void add(SummaryCandidate& cand){
//        list.push(cand);
//    }
//
//    void pop_front(){
//        list.pop();
//    }   
//
//    bool isInWorklist(SummaryCandidate& cand){
//        return false;
//    }
//
//    bool empty(){
//        return list.empty();
//    }
//} ;
//
//bool nonTrivial(SummaryCandidate& newCand){
//    //return true;
//    return !(newCand.from == newCand.to && newCand.amount == 0);
//}
//
//
//namespace std {
//
//  template <>
//  struct hash<SummaryCandidate>
//  {
//    std::size_t operator()(const SummaryCandidate& k) const
//    {
//      using std::size_t;
//      using std::hash;
//
//      // Compute individual hash values for first,
//      // second and third and combine them using XOR
//      // and bit shifting:
//
//      return ((hash<int>()(k.from)
//               ^ (hash<int>()(k.to) << 1)) >> 1)
//               ^ (hash<int>()(k.amount) << 1)
//               ^ (hash<int>()(k.type) << 2);
//    }
//  };
//
//}


class SummaryNode{
public:
    unsigned id;
    // red edge is bracket edge
    // array index is the edge parens id
    vector<NodewithEID> inRedEdgeNodes;
    vector<NodewithEID> outRedEdgeNodes;
    // blue edge is parenthesis edge
    vector<NodewithEID> inBlueEdgeNodes;
    vector<NodewithEID> outBlueEdgeNodes;

    //unordered_set<unsigned> rIncanExEid;
    //unordered_set<unsigned> rOutcanExEid;
    //unordered_set<unsigned> bIncanExEid;
    //unordered_set<unsigned> bOutcanExEid;
    unsigned belongto;

    //// merge will only perform, when this is set to be false;
    //bool merged;

    SummaryNode(unsigned i, unsigned eidNum){
        id = i;
        belongto = i;
        //merged = false;
    }

} ;

//typedef unordered_set<string> CompleteSummaryEdgeSet;


class SummaryGraph{

private: 
    //// -1 not sure, 0 false, 1 true
    //int** rcanExtendMem;
    //int** bcanExtendMem;
public:

    unordered_map<unsigned, unsigned>node2orignodeid;
    unordered_map<unsigned, string>eid2origeidstring;
    vector<SummaryNode*> nodes;
    // input file name
    string filename;
    // the following set contain complete summary edges, i.e. it contains all amount of certain type of summary edge
//    CompleteSummaryEdgeSet cset;

    stringstream convert;

    // TODO can have two numbers, one for red, one for blue.
    // eidNum is number of edge labels + 1, the one extra represent not clear what label it is for the summary edge.
    unsigned eidNum;


    SummaryGraph(const string& f){
        filename = f;
        constructGraph();
    }


    unordered_map<unsigned, string> getEidToOrig(unordered_map<string, unsigned>& str2eid){
        unordered_map<unsigned, string> result;
        for(unordered_map<string, unsigned>::iterator it = str2eid.begin(); it != str2eid.end(); it++){
            result[it->second] = it->first;
        }
        return result;
    }

    void constructGraph(){
        unordered_map<string, unsigned> string2nodeid = readNodes();
        int vtxNum = string2nodeid.size();
        //cout << "Node Number: " << vtxNum << endl;
        nodes.reserve(vtxNum);
        unordered_map<string, unsigned> str2eid = getEdgeIDs();
        eid2origeidstring = getEidToOrig(str2eid);
        eidNum = str2eid.size() + 1;
        for(int i = 0; i < vtxNum; i++){
            nodes.push_back(new SummaryNode(i, str2eid.size()));
        }
        readEdges(string2nodeid, str2eid);
    }


    string getEdgeLabel(const string& l){
        size_t b, e; 
        b = l.find_first_of("\"");
        e = l.find_last_of("\"");
        
        return l.substr(b+1, (e-b-1));
    }


    /***
     *
     * whether the line of edge represent an open parenthesis/bracket
     */
    bool isOpen(string edgeStringLabel){
        return edgeStringLabel.find("o") != string::npos;
    }

    /***
if* return node pair in the string of an edge in the input file
     * node pair returned in string format.
     */
    pair<string, string> getNodePair(string line){
        string delimiter = "->";
        string str = line.substr(0, line.find_first_of("["));
        string::size_type delimiterstart = str.find_first_of(delimiter);
        string from, to;
        from = str.substr(0, delimiterstart);
        to = str.substr(delimiterstart + delimiter.size());
        return make_pair(from, to);

    }
    
    unordered_map<string, unsigned> getEdgeIDs(){
        unordered_map<string, unsigned> result;
        unsigned eid = 0;

        string line;
        ifstream in(filename.c_str(), ifstream::in);

        while(getline(in, line)){
            if(! isEdge(line)){
                continue;
            }

            string edgeLabel = getEdgeLabel(line);
            edgeLabel = edgeLabel.substr(1);
            //cout << "edge label is " << edgeLabel << endl;
            if(result.find(edgeLabel) == result.end()){
                result[edgeLabel] = eid;
                eid++;
            }
        }
        return result;
    }

    unordered_map<string, unsigned> readNodes(){
        unordered_map<string, unsigned> result;
        unsigned nid = 0;

        string line;
        ifstream in(filename.c_str(), ifstream::in);

        while(getline(in, line)){
            if(!isEdge(line)){
                continue;
            } 
            string from, to;
            pair<string, string> nodesstr = getNodePair(line);
            from = nodesstr.first;
            to = nodesstr.second;

            if(result.find(from) == result.end()){
                result[from] = nid;
                unsigned orignodeid;
                stringstream nodestr(from);
                nodestr >> orignodeid;
                node2orignodeid[nid] = orignodeid;
                // cout << "node " << nid << " has original id " << orignodeid << " == " << from << endl;
                nid ++;
            }

            if(result.find(to) == result.end()){
                result[to] = nid;
                unsigned orignodeid;
                stringstream nodestr(to);
                nodestr >> orignodeid;
                node2orignodeid[nid] = orignodeid;
                // cout << "node " << nid << " has original id " << orignodeid << " == " << to << endl;
                nid ++;
            }
        }
        return result;
    }
    
    /***
     *
     * check whether edge string is a bracket
     */
    bool isBracket(string edgeStringLabel){
       return edgeStringLabel.find("b") != string::npos;
    }
    
    bool isParenthesis(string edgeStringLabel){
        return edgeStringLabel.find("p") != string::npos; 
    }


    // read from dot file with specific format.
    void readEdges(unordered_map<string, unsigned>& str2nid, unordered_map<string, unsigned>& str2eid){
        string line;
        ifstream in(filename.c_str(), ifstream::in);
        while(getline(in, line)){
            if(!isEdge(line)){
                continue;
            }
            string from, to;
            pair<string, string> nodes = getNodePair(line);
            string edgeLabel = getEdgeLabel(line);

            if(isOpen(edgeLabel)){
                from = nodes.first;
                to = nodes.second;
            }else{
                from = nodes.second;
                to = nodes.first;
            }
            edgeLabel = edgeLabel.substr(1);

            unsigned fromid = str2nid[from];
            unsigned toid = str2nid[to];

            if(isBracket(edgeLabel)){
                insertBracketEdge(fromid, toid, str2eid[edgeLabel]);
            }else if(isParenthesis(edgeLabel)){
                insertParenthesisEdge(fromid, toid, str2eid[edgeLabel]);
            }else{
                cout << "Error, the edge is neither bracket nor parenthesis.\n";
                exit(1);
            }

        }
    }


    /***
     *
     * insert bracket edge
     */
    void insertBracketEdge(unsigned fid, unsigned tid, unsigned eid){
        //cout << "Edge: " << fid << " to " << tid << " color: red.\n";
        NodewithEID eidToNode(tid, eid);
        NodewithEID eidFromNode(fid, eid);
        nodes[fid]->outRedEdgeNodes.push_back(eidToNode);
        nodes[tid]->inRedEdgeNodes.push_back(eidFromNode);
    }

    /***
     *  insert parenthesis edge
     */
    void insertParenthesisEdge(unsigned fid, unsigned tid, unsigned eid){
        //cout << "Edge: " << fid << " to " << tid << " color: blue.\n";
        NodewithEID eidToNode(tid, eid);
        NodewithEID eidFromNode(fid, eid);
        nodes[fid]->outBlueEdgeNodes.push_back(eidToNode);
        nodes[tid]->inBlueEdgeNodes.push_back(eidFromNode);
    }

    /***
     * judge whether the input line from input file represents an edge
     */
    bool isEdge(const string& line) {
        if(line.find("->") == string::npos) 
            return false; 
        else 
            return true;
    }

    //// To be discarded
    //bool canExtend(unsigned eid, unsigned to, bool red){
    //    return true;
    //    //if(red){
    //    //    return nodes[to]->rIncanExEid.find(eid) != nodes[to]->rIncanExEid.end();
    //    //}else{
    //    //    return nodes[to]->bIncanExEid.find(eid) != nodes[to]->bIncanExEid.end();
    //    //}
    //}

    ////void addNativeSEdgeCand(SummaryNode* node, int from, int restLen, bool redcolor, int curAmount, In_FastDLL<SummaryCandidate>& worklist){
    //void addNativeSEdgeCand(SummaryNode* node, int from, int restLen, bool redcolor, int curAmount, Worklist& worklist, unsigned eid){
    //    //cout << "Current Trace: current node " << node->id << ", rest length: " << restLen << ", current amount: " << "curAmount: " <<  curAmount <<  endl; 
    //    if(redcolor){
    //        // endwith 
    //        if(node->inBlueEdgeNodes.empty() || node->outBlueEdgeNodes.empty()){
    //            int newAmount = curAmount * eidNum + eid; 
    //            SummaryCandidate newCand(from, node->id, newAmount, redcolor);
    //            if((! worklist.isInWorklist(newCand)) && nonTrivial(newCand)){
    //                worklist.add(newCand);
    //                //cout << "add new candidate into worklist: " << newCand.from << " to " << newCand.to << " with color red " << newCand.red << ", amount is " << curAmount << ", eid is " << eid << ", storeAmount is " << newAmount << endl;
    //            }else{
    //                // WORNING: we can do this because we first perform a non backing edge traversal.
    //                // everything is explored
    //                // return;
    //            }
    //        }
    //        // next depth
    //        if(restLen < 1){
    //            return;
    //        }
    //        for(vector<NodewithEID>::iterator nit = node->outRedEdgeNodes.begin(); nit != node->outRedEdgeNodes.end(); nit++){
    //            NodewithEID eidNode = *nit;
    //            SummaryNode* nextNode = nodes[eidNode.nodeID];
    //            unsigned neweid = eidNode.edgeID;
    //            addNativeSEdgeCand(nextNode, from, restLen-1, redcolor, curAmount + 1, worklist, neweid);
    //        }
    //    }else{
    //        // ends with current node
    //        if(node->inRedEdgeNodes.empty() || node->outRedEdgeNodes.empty()){
    //            unsigned newAmount = curAmount * eidNum + eid;
    //            SummaryCandidate newCand(from, node->id, newAmount, redcolor);
    //            if((! worklist.isInWorklist(newCand)) && nonTrivial(newCand)){
    //                worklist.add(newCand);
    //                //cout << "add new candidate into worklist: " << newCand.from << " to " << newCand.to << " with color red " << newCand.red << ", amount is " << curAmount << ", eid is " << eid << ", storeAmount is " << newAmount << endl;
    //            }else{
    //                // WORNING: we can do this because we first perform a non backing edge traversal.
    //                // everything is explored
    //                // return;
    //            }
    //        }
    //        // next depth
    //        if(restLen < 1){
    //            return;
    //        }
    //        for(vector<NodewithEID>::iterator nit = node->outBlueEdgeNodes.begin(); nit != node->outBlueEdgeNodes.end(); nit++){
    //            NodewithEID eidNode = *nit;
    //            unsigned neweid = eidNode.edgeID;
    //            SummaryNode* nextNode = nodes[eidNode.nodeID];
    //            addNativeSEdgeCand(nextNode, from, restLen-1, redcolor, curAmount + 1, worklist, neweid);
    //        }
    //        //if(curAmount < 1){
    //        //    return;
    //        //}
    //        //for(list<SummaryNode*>::iterator it = node->inBlueEdgeNodes.begin(); it != node->inBlueEdgeNodes.end(); it++){
    //        //    SummaryNode* nextNode = *it;
    //        //    addNativeSEdgeCand(nextNode, from, restLen-1, redcolor, curAmount-1, worklist);
    //        //}
    //    }
    //    return;
    //}
    //
    //
    ////void addNativeSEdgeCand(SummaryNode* node, int maxLen, In_FastDLL<SummaryCandidate>& worklist){
    //void addNativeSEdgeCand(SummaryNode* node, int maxLen, Worklist& worklist){
    //    for(vector<NodewithEID>::iterator ait = node->outRedEdgeNodes.begin(); ait != node->outRedEdgeNodes.end(); ait++){
    //        NodewithEID eidNode = *ait;
    //        unsigned eid = eidNode.edgeID;
    //        SummaryNode* nextNode = nodes[eidNode.nodeID];
    //        addNativeSEdgeCand(nextNode, node->id, maxLen-1, true, 1, worklist, eid);
    //    }
    //
    //    for(vector<NodewithEID>::iterator bit = node->outBlueEdgeNodes.begin(); bit != node->outBlueEdgeNodes.end(); bit++){
    //        NodewithEID eidNode = *bit;
    //        unsigned eid = eidNode.edgeID;
    //        SummaryNode* nextNode = nodes[eidNode.nodeID];
    //        addNativeSEdgeCand(nextNode, node->id, maxLen-1, false, 1, worklist, eid);
    //    }
    //}
    //void checkConsecutiveEdges(unsigned nodeID){
    //    unordered_set<unsigned> usednid;
    //    unsigned len = 0;
    //    checkConsecutiveEdges(nodeID, len, usednid);
    //}
    //
    //void checkConsecutiveEdges(unsigned nodeID, unsigned len, unordered_set<unsigned>& usednid){
    //    SummaryNode* node = nodes[nodeID];
    //    if(usednid.find(nodeID) != usednid.end())
    //        return;
    //    usednid.insert(nodeID);
    //    for(vector<NodewithEID>::iterator it = node->outRedEdgeNodes.begin(); it != node->outRedEdgeNodes.end(); it++){
    //        unsigned nextnid = it->nodeID;
    //        checkConsecutiveEdges(nextnid, len+1, usednid);
    //    }
    //    for(vector<NodewithEID>::iterator it = node->inRedEdgeNodes.begin(); it != node->inRedEdgeNodes.end(); it++){
    //        unsigned nextnid = it->nodeID;
    //        checkConsecutiveEdges(nextnid, len+1, usednid);
    //    }
    //    usednid.erase(nodeID);
    //    cout << "check consecutive edges: consecutive edge length: " << len << endl;
    //}


} ;

//inline int notRepeated(Worklist& worklist, Summaries* S, SummaryCandidate& newCand){
//    return 
//        (
//            (!bitmap_bit_p(S->toIdxOf[newCand.from], newCand.to))
//            ||
//            !(bitmap_bit_p(S->summaries[newCand.from][newCand.to], newCand.amount)))
//        &&
//        //(! worklist.isInFDLL(newCand)) ;
//        (! worklist.isInWorklist(newCand)) ;
//} 
//
//// t{cand\4}: -*-> t{S\4}: --->
//// Src_k ::= Src_i Src_j   , where i+j=k
//inline void combineFrontLenFull(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.to][idx], 0, amount, tmpIt){
//            if(cand.amount + amount > maxBound){
//                break;
//            }
//            SummaryCandidate newCand(cand.from, idx, cand.amount + amount, resultType);
//            worklist.add(newCand);
//            //cout << "cflf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//// t{S={0,1}}: ---> t{cand={0,1}}: -*->
//// Src_k ::= Src_i Src_j   , where i+j=k <= n
//inline void combineBackLenFull(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.from], 0, amount, tmpIt){
//            if(cand.amount + amount > maxBound){
//                break;
//            }
//            SummaryCandidate newCand(idx, cand.to, cand.amount + amount, resultType);
//            worklist.add(newCand);
//            //cout << "cblf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
////t{cand={0,1}}: -*-> t{S={0,1}}: <---
//// Src_i ::= Src_k rSrc_j,  where i + j = k <= n
//// rSrc_i ::= Src_j rSrc_k, where i + j = k <= n
//inline void combineFrontRevLenFull(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.to], 0, amount, tmpIt){
//            if(amount < (unsigned)cand.amount){
//                SummaryCandidate newCand(cand.from, idx, cand.amount - amount, resultType);
//                worklist.add(newCand);
//                //cout << "cfrlf1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }else{
//                SummaryCandidate newCand(idx, cand.from, amount - cand.amount, resultType);
//                worklist.add(newCand);
//                //cout << "cfrlf2: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }
//        }
//    }
//}
//
//// t{cand in {0,1}}: <--- t{S = cand}: -*->
////  t0, t0 -> t4; t1, t1 -> t5, t0, t1 -> t5
////  COc_lc ::= rSrc_c Src_o,  where c+o = l <= n
//inline void createCloseOpen(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    if(cand.amount == 0){
//        return;
//    }
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.from][idx], 0, amount, tmpIt){
//            if(amount == 0)
//                continue;
//            if(amount + cand.amount > maxBound){
//                break;
//            }
//            unsigned len = amount + cand.amount;
//            unsigned close = amount;
//            // CO rule: len * maxBound + close
//            unsigned storedAmt =  len * maxBound + close;
//            SummaryCandidate newCand(idx, cand.to, storedAmt, resultType);
//            worklist.add(newCand);
//            //cout << "cco: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newCand.amount / maxBound  << " with close number " << newCand.amount % maxBound << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//
//// t?: -*-> t0: -1->
//inline void combineFrontLen1(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.to][idx], 0, amount, tmpIt){
//            // only check for amount 1 summary edge, 
//            // room for further optimization to remove loop
//            if(amount > 1){
//                break;
//            }
//            SummaryCandidate newCand(cand.from, idx, cand.amount + amount, resultType);
//            worklist.add(newCand);
//            //cout << "cfl1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//
//
//// t0: -1-> t?: -*->
//inline void combineBackLen1(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.from], 0, amount, tmpIt){
//            // only check for amount 1 summary edge, 
//            // room for further optimization to remove loop
//            if(amount > 1){
//                break;
//            }
//            SummaryCandidate newCand(idx, cand.to, cand.amount + amount, resultType);
//            worklist.add(newCand);
//            //cout << "cbl1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//// t?: -*-> t0: <-1-
//// Warning Requirement: cand.amount > 0
//inline void combineFrontRevLen1(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, int resultType){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.to], 0, amount, tmpIt){
//            if(amount > 1){
//                break;
//            }
//            SummaryCandidate newCand(cand.from, idx, cand.amount - 1, resultType);
//            worklist.add(newCand);
//            //cout << "cfrl1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//// Src_prel_ij ::= '[_j' Src_i
//// Src_prer_ij ::= Src_i ']_j' 
//inline void twoSideCombineBlue(SummaryGraph& sGraph, SummaryCandidate& cand, Worklist& worklist){
//    SummaryNode* leftN = sGraph.nodes[cand.from];
//    SummaryNode* rightN = sGraph.nodes[cand.to];
//    // Src_prel_ij ::= '[_j' Src_i
//    for(vector<NodewithEID>::iterator lit = leftN->inBlueEdgeNodes.begin(); lit != leftN->inBlueEdgeNodes.end(); lit++){
//        unsigned eid = lit->edgeID;
//        SummaryNode* a = sGraph.nodes[lit->nodeID];
//        // Src_pre amount rule: len * sGraph.eidNum + eid;
//        unsigned storedAmt = cand.amount * sGraph.eidNum + eid;
//        SummaryCandidate newCand(a->id, cand.to, storedAmt, 2);
//        worklist.add(newCand);
//        //cout << "tscb1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newCand.amount / sGraph.eidNum << " blue eid " << newCand.amount / sGraph.eidNum << ", type is " << newCand.type << endl;
//    }
//
//    // Src_prer_ij ::= Src_i ']_j' 
//    for(vector<NodewithEID>::iterator rit = rightN->inBlueEdgeNodes.begin(); rit != rightN->inBlueEdgeNodes.end(); rit++){
//        unsigned eid = rit->edgeID;
//        SummaryNode* b = sGraph.nodes[rit->nodeID];
//        // Src_pre amount rule: len * sGraph.eidNum + eid;
//        unsigned storedAmt = cand.amount * sGraph.eidNum + eid;
//        SummaryCandidate newCand(cand.from, b->id, storedAmt, 3);
//        worklist.add(newCand);
//        //cout << "tscb2: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newCand.amount / sGraph.eidNum << " blue eid " << newCand.amount / sGraph.eidNum << ", type is " << newCand.type << endl;
//    }
//}
//
//                    
//// COc ::= '[_i' COc ']_i'
//inline void COtwoSideLookup(SummaryGraph& sGraph, SummaryCandidate& cand, Worklist& worklist, unsigned maxBound){
//    // Warning maxBound is only for debug usage
//    SummaryNode* leftN = sGraph.nodes[cand.from];
//    SummaryNode* rightN = sGraph.nodes[cand.to];
//    unordered_map<unsigned, unsigned> leftedges;
//    for(vector<NodewithEID>::iterator lit = leftN->inBlueEdgeNodes.begin(); lit != leftN->inBlueEdgeNodes.end(); lit++){
//        // there are no two in edges has the same eid since we operate on a preprocessed graph.
//        leftedges[lit->edgeID] = lit->nodeID;
//    }
//    for(vector<NodewithEID>::iterator rit = rightN->inBlueEdgeNodes.begin(); rit != rightN->inBlueEdgeNodes.end(); rit++){
//        unsigned edgeID = rit->edgeID;
//        unsigned tonodeID = rit->nodeID;
//        if(leftedges.find(edgeID) != leftedges.end()){
//            SummaryCandidate newCand(leftedges[edgeID], tonodeID, cand.amount, 5);
//            worklist.add(newCand);
//            //cout << "cotsl: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newCand.amount / maxBound << " with close " << newCand.amount % maxBound << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//
//// t1: -*-> t5: <--->>
//// COc_lc ::= Src_k COc_ij, where c = j - k > 0 and l = i - k
//// Src_q ::= Src_k COc_ij, where j - k < 0 and q = (i - j) + (k - j) <= n
//inline void tOneCombineFrontTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    unsigned candamount = cand.amount;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.to][idx], 0, amount, tmpIt){
//            // CO rule: len * maxBound + close
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//            if(tmpclose > candamount){
//                unsigned newlen = tmplen - candamount;
//                unsigned newclose = tmpclose - candamount;
//                unsigned storedAmt = newlen * maxBound + newclose;
//                SummaryCandidate newCand(cand.from, idx, storedAmt, 5);
//                //cout << "tocftf1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " with close number " << newclose << ", type is " << newCand.type << endl;
//                worklist.add(newCand);
//            }else{
//                unsigned tmpopen = tmplen - tmpclose;
//                unsigned storedAmt = tmpopen + candamount - tmpclose;
//                if(storedAmt > maxBound)
//                    continue;
//                SummaryCandidate newCand(cand.from, idx, storedAmt, 1);
//                //cout << "tocftf2: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//                worklist.add(newCand);
//            }
//        }
//    }
//}
//
//// t5: <-*->> t{S={0,1}}: --->
//// COc_lc ::= COc_ic + Src_k, where i + k = l <= n
//inline void tFiveCombineFront(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, bool lenOne){
//    int resultType = 5;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.to][idx], 0, amount, tmpIt){
//            if(lenOne && amount > 1){
//                break;
//            }
//            // CO rule: len * maxBound + close
//            if(cand.amount / maxBound + amount < maxBound){
//                unsigned storedAmt = cand.amount + amount * maxBound;
//                SummaryCandidate newCand(cand.from, idx, storedAmt, resultType);
//                worklist.add(newCand);
//                //cout << "tfcf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }
//        }
//    }
//}
//
//
//// t1: -*-> t5: <<--->
//// rCOc_lc ::= Src_k + rCOc_ic, where i - c > k, l = i - k
//// Src_j ::= Src_k + rCOc_ic, where i - c <= k and j = c + k - (i-c) <= n
//inline void tOneCombineFrontRevTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.to], 0, amount, tmpIt){
//            // CO rule: len * maxBound + close
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//            unsigned tmpopen = tmplen - tmpclose;
//            if(tmpopen > (unsigned)cand.amount){
//                unsigned newlen = tmplen - cand.amount;
//                unsigned newclose = tmpclose;
//                unsigned storedAmt = newlen * maxBound + newclose;
//                SummaryCandidate newCand(idx, cand.from, storedAmt, 5);
//                worklist.add(newCand);
//                //cout << "tocfrtf1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " close number " << newclose << ", type is " << newCand.type << endl;
//            }else{
//                unsigned storedAmt = tmpclose + cand.amount - tmpopen;
//                if(storedAmt > maxBound)
//                    continue;
//                SummaryCandidate newCand(cand.from, idx, storedAmt, 1);
//                worklist.add(newCand);
//                //cout << "tocfrtf2: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }
//        }
//    }
//}
//
//// t5: <-*->> t{S={0,1}}: <---
//// COc_lc ::= COc_ic + rSrc_k, where i - c > k, l = i - k
//// rSrc_j ::= COc_ic + rSrc_k, where i - c <= k and j = c + k - (i - c) <= n 
//inline void tFiveCombineFrontRev(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, bool lenOne){
//    int resultType = 5;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.to], 0, amount, tmpIt){
//            if(lenOne && amount > 1){
//                break;
//            }
//            // CO rule: len * maxBound + close
//            unsigned len = cand.amount / maxBound;
//            unsigned close = cand.amount % maxBound;
//            unsigned open = len - close;
//            if(open <= amount){
//                SummaryCandidate newCand(idx, cand.from, close + amount - open, 1);
//                if(newCand.amount > (int)maxBound)
//                    continue;
//                worklist.add(newCand);
//                //cout << "tfcfr2: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }else{
//                len = len - amount;
//                unsigned storedAmt = len * maxBound + close;
//                SummaryCandidate newCand(cand.from, idx, storedAmt, resultType);
//                worklist.add(newCand);
//                //cout << "tfcfr1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }
//        }
//    }    
//}
//
//// t5: <--->> t1: -*->
//// COc_lc ::= COc_ic + Src_k, where i + k = l <= n
//inline void tOneCombineBackTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.from], 0, amount, tmpIt){
//            // CO rule: len * maxBound + close
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//
//            unsigned newlen = tmplen + cand.amount;
//            if(newlen > maxBound)
//                continue;
//            unsigned newclose = tmpclose;
//            unsigned storedAmt = newlen * maxBound + newclose;
//            SummaryCandidate newCand(idx, cand.to, storedAmt, 5);
//            worklist.add(newCand);
//            //cout << "tocbtf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//// t{S={0,1}}: ---> t5: <-*->>
//// COc_lc ::= Src_k COc_ij, where c = j - k > 0 and l = i - k
//// Src_q ::= Src_k COc_ij, where j - k < 0 and q = (i - j) + (k - j) <= n
//inline void tFiveCombineBack(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, bool lenOne){
//    int resultType = 5;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.from], 0, amount, tmpIt){
//            if(lenOne && amount > 1){
//                break;
//            }
//            // CO rule: len * maxBound + close
//            unsigned len = cand.amount / maxBound;
//            unsigned close = cand.amount % maxBound;
//            if(close <= amount){
//                SummaryCandidate newCand(idx, cand.to, len - close + amount - close, 1);
//                if(newCand.amount < (int)maxBound)
//                    continue;
//                worklist.add(newCand);
//                //cout << "tfcb2: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }else{
//                len -= amount;
//                close -= amount;
//                unsigned storedAmt = len * maxBound + close;
//                SummaryCandidate newCand(idx, cand.to, storedAmt, resultType);
//                worklist.add(newCand);
//                //cout << "tfcb1: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }
//        }
//    }
//}
//
//// t5: <<---> t1: -*->
//// rCOc_lc ::= rCOc_ij Src_k, where l = i + k <= n and c = k + j
//inline void tOneCombineBackRevTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.from][idx], 0, amount, tmpIt){
//            // CO rule: len * maxBound + close
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//
//            unsigned newlen = tmplen + cand.amount;
//            if(newlen > maxBound)
//                continue;
//            unsigned newclose = tmpclose + cand.amount;
//            unsigned storedAmt = newlen * maxBound + newclose;
//            SummaryCandidate newCand(cand.to, idx, storedAmt, 5);
//            worklist.add(newCand);
//            //cout << "tocbrtf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " with close number " << newclose << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//                    
//// t{S={0,1}}: <--- t5: <-*->>
//// COc_lc ::= rSrc_k COc_ij, where l = i + k <= n and c = k + j 
//inline void tFiveCombineBackRev(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist, bool lenOne){
//    int resultType = 5;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.from][idx], 0, amount, tmpIt){
//            if(lenOne && amount > 1){
//                break;
//            }
//            // CO rule: len * maxBound + close
//            if(cand.amount / maxBound + amount < maxBound){
//                unsigned len = cand.amount / maxBound;
//                len += amount;
//                unsigned close = cand.amount % maxBound;
//                close += amount;
//                unsigned storedAmt = len * maxBound + close;
//                SummaryCandidate newCand(idx, cand.to, storedAmt, resultType);
//                worklist.add(newCand);
//                //cout << "tfcbr: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with amount " << newCand.amount << ", type is " << newCand.type << endl;
//            }
//        }
//    }
//}
//
//// t5: <-*->> t5: <--->>
//// COc_lc ::= COc_ab COc_ij, where l = a + i - 2*min(a-b, j) <= n and c = b + max(j-(a-b), 0)
//inline void tFiveCombineFrontTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    // CO rule: len * maxBound + close
//    unsigned candlen = cand.amount / maxBound;
//    unsigned candclose = cand.amount % maxBound;
//    unsigned candopen = candlen - candclose;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.to][idx], 0, amount, tmpIt){
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//            
//            unsigned merged = 2 * min(candopen, tmpclose);
//            unsigned newlen = candlen + tmplen - merged;
//            if(newlen > maxBound){
//                continue;
//            }
//            unsigned newclose = candclose + max(((int)tmpclose-(int)candopen), 0);
//            unsigned storedAmt = newlen * maxBound + newclose; 
//            SummaryCandidate newCand(cand.from, idx, storedAmt, 5);
//            worklist.add(newCand);
//            //cout << "tfcftf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " with close number " << newclose << ", type is " << newCand.type << endl;
//        }
//    }
//}
//
//                    
//// t5: <-*->> t5: <<--->
//// COc_lc ::= COc_ab rCOc_ij, where l = a + i - 2*min(a-b, i-j) <= n and c = b + max((i-j)-(a-b), 0)
//inline void tFiveCombineFrontRevTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    // CO rule: len * maxBound + close
//    unsigned candlen = cand.amount / maxBound;
//    unsigned candclose = cand.amount % maxBound;
//    unsigned candopen = candlen - candclose;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.to], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.to], 0, amount, tmpIt){
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//            unsigned tmpopen = tmplen - tmpclose;
//            
//            unsigned merged = 2 * min(candopen, tmpopen);
//            unsigned newlen = candlen + tmplen - merged;
//            if(newlen > maxBound){
//                continue;
//            }
//            unsigned newclose = candclose + max(((int)tmpopen-(int)candopen), 0);
//            unsigned storedAmt = newlen * maxBound + newclose; 
//            SummaryCandidate newCand(cand.from, idx, storedAmt, 5);
//            worklist.add(newCand);
//            //cout << "tfcfrtf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " with close number " << newclose << ", type is " << newCand.type << endl;
//        }
//    }
//}
//                    
//// t5: <--->> t5: <-*->>
//// COc_lc ::= COc_ab COc_ij, where l = a + i - 2*min(a-b, j) <= n and c = b + max(j-(a-b), 0)
//inline void tFiveCombineBackTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    // CO rule: len * maxBound + close
//    unsigned candlen = cand.amount / maxBound;
//    unsigned candclose = cand.amount % maxBound;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.fromIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[idx][cand.from], 0, amount, tmpIt){
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//            unsigned tmpopen = tmplen - tmpclose;
//            
//            unsigned merged = 2 * min(candclose, tmpopen);
//            unsigned newlen = candlen + tmplen - merged;
//            if(newlen > maxBound){
//                continue;
//            }
//            unsigned newclose = tmpclose + max(((int)candclose-(int)tmpopen), 0);
//            unsigned storedAmt = newlen * maxBound + newclose; 
//            SummaryCandidate newCand(idx, cand.to, storedAmt, 5);
//            worklist.add(newCand);
//            //cout << "tfcbtf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " with close number " << newclose << ", type is " << newCand.type << endl;
//        }
//    }
//}
//                    
//// t5: <<---> t5: <-*->>
//// COc_lc ::= rCOc_ab COc_ij, where l = a + i - 2 * min(b, j) <= n and c = (a-b) + max(j-b, 0)
//inline void tFiveCombineBackRevTFive(Summaries& S, SummaryCandidate& cand, unsigned maxBound, Worklist& worklist){
//    // CO rule: len * maxBound + close
//    unsigned candlen = cand.amount / maxBound;
//    unsigned candclose = cand.amount % maxBound;
//    unsigned idx;
//    bitmap_iterator bitIt;
//    EXECUTE_IF_SET_IN_BITMAP(S.toIdxOf[cand.from], 0, idx, bitIt){
//        unsigned amount;
//        bitmap_iterator tmpIt;
//        EXECUTE_IF_SET_IN_BITMAP(S.summaries[cand.from][idx], 0, amount, tmpIt){
//            unsigned tmplen = amount / maxBound;
//            unsigned tmpclose = amount % maxBound;
//            unsigned tmpopen = tmplen - tmpclose;
//            
//            unsigned merged = 2 * min(candclose, tmpclose);
//            unsigned newlen = candlen + tmplen - merged;
//            if(newlen > maxBound){
//                continue;
//            }
//            unsigned newclose = tmpopen + max(((int)candclose-(int)tmpclose), 0);
//            unsigned storedAmt = newlen * maxBound + newclose; 
//            SummaryCandidate newCand(idx, cand.to, storedAmt, 5);
//            worklist.add(newCand);
//            //cout << "tfcbrtf: add new summary candidate: " << newCand.from << " -> " << newCand.to << " with len " << newlen << " with close number " << newclose << ", type is " << newCand.type << endl;
//        }
//    }
//}

unsigned root(unsigned id, SummaryGraph& sGraph){
    SummaryNode* node = sGraph.nodes[id];
    if(node->id != node->belongto){
        node->belongto = root(sGraph.nodes[node->belongto]->id, sGraph);
    }
    return node->belongto;
    // postcondition: root(node).belongto == node
    // node.belongto = root(node)
}

//// precondition: blue edges are dk preprocessed
//void mergeTwoNodes(unsigned id1, unsigned id2, list<pair<unsigned, Summaries*> >& listS, SummaryGraph& sGraph, Worklist& worklist){
//    if(root(id1, sGraph) != id1 || root(id2, sGraph) != id2){
//        return mergeTwoNodes(root(id1, sGraph), root(id2, sGraph), listS, sGraph, worklist);
//    }
//    if(id1 == id2){
//        return;
//    }
//    queue<pair<unsigned, unsigned>> mergelist;
//    unordered_map<unsigned, unsigned> n1inedges;
//    SummaryNode* node1 =  sGraph.nodes[id1];
//    SummaryNode* node2 =  sGraph.nodes[id2];
//
//    // move blue edges
//    for(vector<NodewithEID>::iterator ait = node1->inBlueEdgeNodes.begin(); ait != node1->inBlueEdgeNodes.end(); ait++){
//        n1inedges[ait->edgeID] = ait->nodeID;
//    }
//    for(vector<NodewithEID>::iterator bit = node2->inBlueEdgeNodes.begin(); bit != node2->inBlueEdgeNodes.end(); bit++){
//        unsigned fromid = bit->nodeID;
//        unsigned eid = bit->edgeID;
//        if(n1inedges.find(eid) != n1inedges.end()){
//            if(fromid != n1inedges[eid]){
//                // add to merge list first
//                mergelist.push(make_pair(fromid, n1inedges[eid]));
//            }else{
//                // no problem
//            }
//            continue;
//        }
//        NodewithEID eidNode(fromid, eid);
//        node1->inBlueEdgeNodes.push_back(eidNode);
//    }
//    node2->inBlueEdgeNodes.clear();
//
//
//    // move summary edges
//    for(list<pair<unsigned, Summaries*> >::iterator lit = listS.begin(); lit != listS.end(); lit++){
//        Summaries* S = (*lit).second;
//        unsigned type = (*lit).first;
//
//        unsigned idx;
//        bitmap_iterator bitIt;
//        EXECUTE_IF_SET_IN_BITMAP(S->toIdxOf[id2], 0, idx, bitIt){
//            unsigned amount;
//            bitmap_iterator tmpIt;
//            EXECUTE_IF_SET_IN_BITMAP(S->summaries[id2][idx], 0, amount, tmpIt){
//                SummaryCandidate newCand(id2, idx, amount, type);
//                worklist.add(newCand);
//            }
//            bitmap_clear(S->summaries[id2][idx]);
//            bitmap_clear_bit(S->toIdxOf[id2], idx);
//            bitmap_clear_bit(S->fromIdxOf[idx], id2);
//        }
//
//        EXECUTE_IF_SET_IN_BITMAP(S->fromIdxOf[id2], 0, idx, bitIt){
//            unsigned amount;
//            bitmap_iterator tmpIt;
//            EXECUTE_IF_SET_IN_BITMAP(S->summaries[idx][id2], 0, amount, tmpIt){
//                SummaryCandidate newCand(idx, id2, amount, type);
//                worklist.add(newCand);
//            }
//            bitmap_clear(S->summaries[idx][id2]);
//            bitmap_clear_bit(S->toIdxOf[idx], id2);
//            bitmap_clear_bit(S->fromIdxOf[id2], idx);
//        }
//    }
//    // cout << id1 << " and " << id2 << " finish this twonodemerge.\n";
//    // postcondition, move all summary edges related to id2 to id1
//    // update summary toIdxOf/fromIdxOf accordingly
//
//
//    node2->belongto = node1->id;
//    
//    while(!mergelist.empty()){
//        unsigned aid = mergelist.front().first;
//        unsigned bid = mergelist.front().second;
//        mergeTwoNodes(aid, bid, listS, sGraph, worklist);
//        mergelist.pop();
//    }
//    // post condition: root(node2).belongto = root(node1); node1.belongto = node2.belong = root(node1)
//}
//
//class SearchNode{
//public:
//    unsigned nid;
//    unsigned depth;
//    SearchNode(unsigned n, unsigned d){
//        nid = n;
//        depth = d;
//    }
//    bool operator<(const SearchNode& other) const{
//        return depth > other.depth;
//    }
//} ;
//
//void moveCycle(SummaryGraph& sGraph, unsigned nodeid, unsigned len, unsigned close, Worklist& worklist, unsigned maxBound){
//    unordered_set<unsigned> usednid;
//
//    priority_queue<SearchNode> searchedNodes;
//    SearchNode snode(nodeid, 0);
//    searchedNodes.push(snode);
//    while(!searchedNodes.empty()){
//        // blue edge exists on current node
//        SearchNode cursNode = searchedNodes.top();
//        searchedNodes.pop();
//        if(usednid.find(cursNode.nid) != usednid.end()){
//            continue;
//        }
//        usednid.insert(cursNode.nid);
//        SummaryNode* n = sGraph.nodes[cursNode.nid];
//        unsigned exclose = cursNode.depth;
//        unsigned newclose = close + exclose;
//        unsigned newlen = len + 2 * exclose;
//        if(newlen > maxBound){
//            break;
//        }
//        for(vector<NodewithEID>::iterator it = n->inBlueEdgeNodes.begin(); it != n->inBlueEdgeNodes.end(); it++){
//            unsigned nextnid = it->nodeID;
//            // CYCOc rule: len * maxBound + close
//            unsigned storedAmt = newlen * maxBound + newclose;
//            // one direction
//            SummaryCandidate newCandX(nextnid, nextnid, storedAmt, 5);
//            worklist.add(newCandX);
//            //cout << "mc1: add new summary candidate: " << newCandX.from << " -> " << newCandX.to << " with len " << len << " with close number " << close << ", type is " << newCandX.type << endl;
//        }
//
//        for(vector<NodewithEID>::iterator it = n->inRedEdgeNodes.begin(); it != n->inRedEdgeNodes.end(); it++){
//            unsigned nextnid = sGraph.nodes[it->nodeID]->belongto;
//            SearchNode newSNode(nextnid, close);
//            searchedNodes.push(newSNode);
//        }
//
//        for(vector<NodewithEID>::iterator it = n->outRedEdgeNodes.begin(); it != n->outRedEdgeNodes.end(); it++){
//            unsigned nextnid = sGraph.nodes[it->nodeID]->belongto;
//            SearchNode newSNode(nextnid, close+1);
//            searchedNodes.push(newSNode);
//        }
//    }
//
//}
//// move cycle after a blue incoming edge.
//// the final summary edge should contain minimal close number
//void moveCycleTOne(SummaryCandidate& cand, SummaryGraph& sGraph, Worklist& worklist, unsigned maxBound){
//    unsigned nodeid = cand.from;
//    moveCycle(sGraph, nodeid, cand.amount, 0, worklist, maxBound);
//}
//
//void moveCycleTFive(SummaryCandidate& cand, SummaryGraph& sGraph, Worklist& worklist, unsigned maxBound){
//    unsigned nodeid = cand.from;
//    unsigned len = cand.amount / maxBound;
//    unsigned close = cand.amount % maxBound;
//    moveCycle(sGraph, nodeid, len, close, worklist, maxBound);
//}
//
//bool isCycle(SummaryCandidate& cand){
//    return cand.from == cand.to;
//}


#endif

