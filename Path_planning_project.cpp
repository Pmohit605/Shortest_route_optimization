
#include <bits/stdc++.h>

using namespace std;

#define ENV_DIM  20
typedef char Env[ENV_DIM][ENV_DIM] ;







#define NODE_LIST_ARRAY_MAX_SIZE    4*(ENV_DIM * ENV_DIM)







class Node{
 
    public :
  int getRow()
    {
        return this->row ;
    }

    int getCol()
    {
        return this->col ;
    }

    int getDistanceTraveled()
    {
        return dist_traveled ;
    }
   
     void setDistanceTraveled( int dist_traveled )
     {
         this->dist_traveled = dist_traveled ;
     }
   
    int getEstimatedDist2Goal( Node goal )
    {
        int x2 = goal.getRow() ;
        int y2 = goal.getCol() ;

         int x1 = this->row ;
         int y1 = this->col ;  
        int manhattan_dist = abs( x1-x2) + abs(y1-y2) ;

        return manhattan_dist ;
    }
   
    Node(int row, int col, int dist_traveled)
     {
        this->row = row ;
        this->col = col ;
        this->dist_traveled = dist_traveled ;
     }
     
     bool operator<(const Node& t) const
    {
        return (this->row < t.row);
    }
     
     Node()
    {
        this->row = 0;
        this->col = 0 ;
        this->dist_traveled = 0 ;

    }
   
   /* ~Node()
    {
        cout<<"Destructor Invoked\n";
    }*/
 
  private:
    int row;
    int col;
    int dist_traveled;

 
 
 
 
   
};


vector<pair<int,int>> solution_path_pair ;

class NodeList{
   
    public:
   
    NodeList()
    {
        length =0 ;
    }
   
    int getLength()
    {
        return length ;
    }
   
    void addElement( Node *newNode )
    {

        if( length == NODE_LIST_ARRAY_MAX_SIZE )
        {
            cout<<" Limit reached , cannot add more\n" ;
            return ;
        }

        nodes[length] = newNode ;
        length++ ;
       

       
        return ;
    }
   
    Node* getNode( int i )
    {
        if( i >= length )
        {
            cout<<" INDEX OUT OF BOND , NO NODE AVAILABLE FOR THIS INDEX\n" ;
            Node tmp(-1,-1,-1);
            return NULL ;;
        }

       
        return nodes[i]  ;
    }
   
    bool isEmpty( int curr_index )
    {
        if( curr_index == length )
        {
            return true ;
        }
        return false;
    }
   
    private:
        Node* nodes[NODE_LIST_ARRAY_MAX_SIZE];
        int length;
       
   
};




struct node_for_back_tracking{
 
  int previous_row_index ;
  int previous_col_index ;
 
  double parent_dist,parent_heurstc_dist ;
  int  parent_dist_travelled;
};



bool can_we_go_to_this_cell( Node a , Env env)
{
    int roww = a.getRow() ;
    int coll = a.getCol() ;
   
    if( (roww <0 || roww >=20)  )
    {
        return false ;
    }
   
    if( (coll <0 || coll >=20)  )
    {
        return false ;
    }
   
    if( env[roww][coll] == '=' )
    {
        return false ;
    }
   
    return true ;
   
}

bool is_this_goal_node( Node a , Node goal )
{
    if( (a.getRow() == goal.getRow()) && ( a.getCol() == goal.getCol() ) )
    {
        return true ;
    }
   
    return false;
}

double manhattan_dist( Node a , Node goal  )
{
   
    int x1 = a.getRow() ;
    int y1 = a.getCol() ;
   
    int x2 = goal.getRow() ;
    int y2 = goal.getCol() ;
   
    int k1 = (x1-x2)*(x1-x2) ;
    int k2 = (y1-y2)*(y1-y2) ;
    return ( (double)sqrt( k1+ k2  ) ) ;
   
}


void getPath(node_for_back_tracking array[][ENV_DIM], Node goal)
{
    cout<<" REQUIRED PATH ->\n" ;
    int row = goal.getRow();
    int col = goal.getCol();
 
    stack<pair<int,int>> Path;
 
 
 
    while (!(array[row][col].previous_row_index == row && array[row][col].previous_col_index == col))
    {
        Path.push(make_pair(row, col));
        int temp_row = array[row][col].previous_row_index;
        int temp_col = array[row][col].previous_col_index;
        row = temp_row;
        col = temp_col;
       
    }
 
 NodeList req_list ;
 int o =0 ;
 int sz = Path.size() ;
 Node arr[sz] ;
 int index =0 ;
    Path.push(make_pair(row, col));
   
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Node s(p.first,p.second,o);
         
        o++ ;
        arr[index] = s ;
       
        index++ ;
        Path.pop();
       
       
    }
 
 for( int k =0 ; k<sz ; k++ )
 {
     req_list.addElement(&arr[k]) ;
 }


 index =0 ;
while( !req_list.isEmpty(index) )
{
    Node *a = req_list.getNode(index) ;
   
    index++ ;
    cout<<(*a).getRow()<<","<<(*a).getCol()<<"\n";
    int k1 = (*a).getRow() ;
    int k2 = (*a).getCol() ;
    solution_path_pair.push_back({k1,k2});
}
 


 
    return;
}

void help( Env env , Node src , Node goal )
{
   
    if( can_we_go_to_this_cell(src,env) && can_we_go_to_this_cell(goal,env) )
    {
        cout<<" BOTH SOURCE AND DESTINATION ARE VALID\n";
    }
    else
    {
        cout<<" INVALID INPUT IN SORCE OR DESTINATION\n" ;
        return ;
    }
   
    if( is_this_goal_node(src,goal) )
    {
        cout<<"BOTH SOURCE AND DESTINATION ARE SAME\n" ;
        return ;
    }
   
    bool closed_List_C[ENV_DIM][ENV_DIM];
   
   
    for( int i =0 ; i<ENV_DIM ; i++  )
    {
        for( int j =0 ; j<ENV_DIM ; j++ )
        {
            closed_List_C[i][j] = false ;
        }
    }
   
    node_for_back_tracking parent_to_child_cell[ENV_DIM][ENV_DIM];
   
    int i,j ;
   
    for (i = 0; i < ENV_DIM ; i++) {
        for (j = 0; j < ENV_DIM ; j++) {
            parent_to_child_cell[i][j].parent_dist = FLT_MAX;
            parent_to_child_cell[i][j].parent_heurstc_dist= INT_MAX;
            parent_to_child_cell[i][j].parent_heurstc_dist = FLT_MAX;
            parent_to_child_cell[i][j].previous_row_index = -1;
            parent_to_child_cell[i][j].previous_col_index = -1;
        }
    }
   
     i = src.getRow(), j = src.getCol();
    parent_to_child_cell[i][j].parent_dist = 0.0;
    parent_to_child_cell[i][j].parent_heurstc_dist= 0;
    parent_to_child_cell[i][j].parent_heurstc_dist = 0.0;
    parent_to_child_cell[i][j].previous_row_index = i;
    parent_to_child_cell[i][j].previous_col_index = j;
   
    set<pair<double,Node>> openList ;
    openList.insert({0.0,src}) ;
    bool foundDest = false;
   
    NodeList nodesExplored ;
   
    while( !openList.empty() )
    {
       
        pair<double,Node> curr_node = *openList.begin() ;
        openList.erase(openList.begin());
        i = curr_node.second.getRow();
        j = curr_node.second.getCol();
       
        nodesExplored.addElement(&(curr_node.second)) ;
       // cout<<i<<" "<<j<<"      \n" ;
        closed_List_C[i][j] = true;
        Node node_of_curr_val =  curr_node.second;
          double  manhtan_dist, new_tot_heuristic;
          int distance_traversed_from_sorce ;
         
          Node up(node_of_curr_val.getRow()-1,node_of_curr_val.getCol(),parent_to_child_cell[i][j].parent_heurstc_dist+ 1);
          Node down(node_of_curr_val.getRow()+1,node_of_curr_val.getCol(),parent_to_child_cell[i][j].parent_heurstc_dist+ 1);
          Node left(node_of_curr_val.getRow(),node_of_curr_val.getCol()-1,parent_to_child_cell[i][j].parent_heurstc_dist+ 1);
          Node right(node_of_curr_val.getRow(),node_of_curr_val.getCol()+1,parent_to_child_cell[i][j].parent_heurstc_dist+ 1);
         
          if( can_we_go_to_this_cell(up,env) )
          {
             
              if( is_this_goal_node(up,goal) )
              {
                  cout<<" REACHED THE GOAL SMILEY\n" ;
                  foundDest = true ;
                   int rr = up.getRow() ;
                  int cc = up.getCol() ;
                  parent_to_child_cell[rr][cc].previous_row_index = i ;
                  parent_to_child_cell[rr][cc].previous_col_index = j ;
                  getPath(parent_to_child_cell, goal);
                   return ;
              }
               else
              {
                    if( closed_List_C[i-1][j] == false )
                    {
                            distance_traversed_from_sorce = parent_to_child_cell[i][j].parent_heurstc_dist+ 1;
                            manhtan_dist = manhattan_dist(up, goal);
                            new_tot_heuristic = distance_traversed_from_sorce + manhtan_dist;
                           
                             if (parent_to_child_cell[i - 1][j].parent_dist == FLT_MAX || parent_to_child_cell[i - 1][j].parent_dist > new_tot_heuristic)
                                {
                                   
                                       // cout<<" up\n";
                                    openList.insert({new_tot_heuristic,up});
                                    parent_to_child_cell[i - 1][j].parent_dist = new_tot_heuristic;
                                    parent_to_child_cell[i - 1][j].parent_heurstc_dist= distance_traversed_from_sorce;
                                    parent_to_child_cell[i - 1][j].parent_heurstc_dist = manhtan_dist;
                                    parent_to_child_cell[i - 1][j].previous_row_index = i;
                                    parent_to_child_cell[i - 1][j].previous_col_index = j;
                                }
                    }
              }
             
             
          }
         
         
           if( can_we_go_to_this_cell(down,env) )
          {
             
              if( is_this_goal_node(down,goal) )
              {
                  cout<<" REACHED THE GOAL SMILEY\n" ;
                  foundDest = true ;
                  int rr = down.getRow() ;
                  int cc = down.getCol() ;
                  parent_to_child_cell[rr][cc].previous_row_index = i ;
                  parent_to_child_cell[rr][cc].previous_col_index = j ;
                 
                 
                  getPath(parent_to_child_cell, goal);
                   return ;
              }
               else
              {
                    if( closed_List_C[i+1][j] == false )
                    {
                            distance_traversed_from_sorce = parent_to_child_cell[i][j].parent_heurstc_dist+ 1 ;
                            manhtan_dist = manhattan_dist(down, goal);
                            new_tot_heuristic = distance_traversed_from_sorce + manhtan_dist;
                           
                             if (parent_to_child_cell[i + 1][j].parent_dist == FLT_MAX || parent_to_child_cell[i + 1][j].parent_dist > new_tot_heuristic)
                                {
                                   
                                     // cout<<" down\n";  
                                    openList.insert({new_tot_heuristic,down});
                                    parent_to_child_cell[i + 1][j].parent_dist = new_tot_heuristic;
                                    parent_to_child_cell[i + 1][j].parent_heurstc_dist= distance_traversed_from_sorce;
                                    parent_to_child_cell[i + 1][j].parent_heurstc_dist = manhtan_dist;
                                    parent_to_child_cell[i + 1][j].previous_row_index = i;
                                    parent_to_child_cell[i + 1][j].previous_col_index = j;
                                }
                    }
              }
             
             
          }
         
          if( can_we_go_to_this_cell(left,env) )
          {
             
              if( is_this_goal_node(left,goal) )
              {
                  cout<<" REACHED THE GOAL SMILEY\n" ;
                  foundDest = true ;
                   int rr = left.getRow() ;
                  int cc = left.getCol() ;
                  parent_to_child_cell[rr][cc].previous_row_index = i ;
                  parent_to_child_cell[rr][cc].previous_col_index = j ;
                  getPath(parent_to_child_cell, goal);
                   return ;
              }
               else
              {
                    if( closed_List_C[i][j-1] == false )
                    {
                            distance_traversed_from_sorce = parent_to_child_cell[i][j].parent_heurstc_dist+ 1 ;
                            manhtan_dist = manhattan_dist(left, goal);
                            new_tot_heuristic = distance_traversed_from_sorce + manhtan_dist;
                           
                             if (parent_to_child_cell[i][j-1].parent_dist == FLT_MAX || parent_to_child_cell[i][j-1].parent_dist > new_tot_heuristic)
                                {
                                   
                                       // cout<<" left\n";
                                    openList.insert({new_tot_heuristic,left});
                                    parent_to_child_cell[i][j - 1].parent_dist = new_tot_heuristic;
                                    parent_to_child_cell[i][j - 1].parent_heurstc_dist= distance_traversed_from_sorce;
                                    parent_to_child_cell[i][j - 1].parent_heurstc_dist = manhtan_dist;
                                    parent_to_child_cell[i][j - 1].previous_row_index = i;
                                    parent_to_child_cell[i][j - 1].previous_col_index = j;
                                }
                    }
              }
             
             
          }
         
        // cout<<right.getRow()<<" "<<right.getCol()<<" "<<env[right.getRow()][right.getCol()]<<"\n";
          if( can_we_go_to_this_cell(right,env) )
          {
             
             
              if( is_this_goal_node(right,goal) )
              {
                  cout<<" REACHED THE GOAL SMILEY\n" ;
                  foundDest = true ;
                   int rr = right.getRow() ;
                  int cc = right.getCol() ;
                  parent_to_child_cell[rr][cc].previous_row_index = i ;
                  parent_to_child_cell[rr][cc].previous_col_index = j ;
                  getPath(parent_to_child_cell, goal);
                  return ;
              }
               else
              {
                    if( closed_List_C[i][j+1] == false )
                    {
                            distance_traversed_from_sorce = parent_to_child_cell[i][j].parent_heurstc_dist+ 1 ;
                            manhtan_dist = manhattan_dist(right, goal);
                            new_tot_heuristic = distance_traversed_from_sorce + manhtan_dist;
                           
                             if (parent_to_child_cell[i][j+1].parent_dist == FLT_MAX || parent_to_child_cell[i][j+1].parent_dist > new_tot_heuristic)
                                {
                                   
                                       // cout<<" right\n";
                                    openList.insert({new_tot_heuristic,right});
                                    parent_to_child_cell[i][j + 1].parent_dist = new_tot_heuristic;
                                    parent_to_child_cell[i][j + 1].parent_heurstc_dist= distance_traversed_from_sorce;
                                    parent_to_child_cell[i][j + 1].parent_heurstc_dist = manhtan_dist;
                                    parent_to_child_cell[i][j + 1].previous_row_index = i;
                                    parent_to_child_cell[i][j + 1].previous_col_index = j;
                                }
                    }
              }
             
             
          }
         
         
         
         
 
    }
   
   
    if ( !foundDest )
       {
           cout<<"NOT ABLE TO REACH DESTINATION\n";
       }
       
       return ;
   
}

void forwardSearch( Env env )
{
    Node src(5,1,0) ;
    Node goal(11,5,INT_MAX) ;
   
   
   
  help( env , src , goal ) ;

}




int main()
{
   
   
   
    Env env ;
   
    for( int i =0 ; i<20 ; i++ )
    {
        for( int j =0 ; j<20 ; j++ )
        {
            cin>>env[i][j] ;
        }
    }
   
    cout<<"hello\n" ;
   
    forwardSearch(env);
    cout<<env[5][1]<<" "<<env[11][5]<<"\n...............\n" ;
   solution_path_pair.push_back({11,5});
   for( int i =0 ; i<solution_path_pair.size()-1 ; i++ )
   {
       int x1 = solution_path_pair[i].first ;
       int y1 = solution_path_pair[i].second ;
       
       int x2 = solution_path_pair[i+1].first ;
       int y2 = solution_path_pair[i+1].second ;
       
       int x = x2 - x1 ;
       int y = y2 - y1 ;
       
       if( x == -1 )
       {
           env[x1][y1] = '^';
           continue ;
       }
        if( x == 1 )
       {
           env[x1][y1] = 'v';
           continue ;
       }
        if( y == -1 )
       {
           env[x1][y1] = '<';
           continue ;
       }
       if( y == 1 )
       {
           env[x1][y1] = '>';
           continue ;
       }
       
   }
env[5][1] = 'S';
 for( int i =0 ; i<20 ; i++ )
    {
        for( int j =0 ; j<20 ; j++ )
        {
            cout<<env[i][j]<<" " ;
        }cout<<"\n";
    }


    return 0;
}

