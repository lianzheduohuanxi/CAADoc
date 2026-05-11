var index; 
var lastDec; 
function sort_int(p1,p2) { 
 var ret=p1[0]-p2[0];
 if(0==ret) {ret=p1[1]-p2[1];} 
 return ret; 
}
function sort_intDesc(p1,p2) { 
 var ret=p2[0]-p1[0]; // return p2[0]-p1[0];
 if(0==ret) {ret=p2[1]-p1[1];}
 return ret;    
}
function sort_charc(c1,c2){  
    if(c1>c2) {return 1;}  
    else if(c1<c2) { return -1;}  
    else return 0;  
} 
function sort_charlw(c1,c2){ 
    var cl1=c1.toLocaleLowerCase(); 
    var cl2=c2.toLocaleLowerCase(); 
    if(cl1>cl2) {return 1;}  
    else if(cl1<cl2) { return -1;}  
    else { return sort_charc(c1,c2);}   
} 
function sort_string(s1,s2){ 
   var rescmp=sort_charlw(s1,s2);    
   return rescmp;     
} 
function sort_char(p1,p2) {  
    var ret=sort_string(p1[0],p2[0]); 
    if(0==ret) ret=p1[1]-p2[1];  
    return ret; 
}    
function sort_charDesc(p1,p2) { 
    var ret=sort_string(p2[0],p1[0]);  
    if(0==ret) ret=p2[1]-p1[1];  
    return ret;    
} 
function TableOrder(e,Dec,iindex,itype)  
{ 
if ( index==iindex && lastDec==Dec ) { return;}  
    else{ 
        index=iindex; 
        lastDec=Dec; 
    }   
    var thisobject=e.srcElement?e.srcElement:e.target; 
    thisobject.style.color='orange';   
    var FntSort = new Array(); 
    index=iindex;     
    var oCell; 
    var oTable; 
    if(!e) e=window.event; 
    for(oTable=e.srcElement?e.srcElement:e.target;oTable.tagName!="TABLE";oTable=oTable.parentNode);   
    //---- Copier Tableau Html dans Table JavaScript ----// 
    var Table = new Array(); 
    var nbRow=oTable.rows.length; //nbligne
    var nbCell=oTable.rows[0].cells.length; // nbcolonne 
    var sortFunct; 
    var objet; 
    for(r=1;r<nbRow;r++) Table[r-1] = new Array(); 
    if(navigator.appName=="Netscape"){ 
        //alert ("Netscape"); 
        for(r=1;r<nbRow;r++) {        //De toutes les rangées          
            objet= oTable.rows[r].cells[index].innerHTML; 
            Table[r-1][0]=objet.replace(/<\/?[^>]+>/gi,""); //nombre  
            Table[r-1][1]=r;
            Table[r-1][2]=oTable.rows[r].innerHTML;      
        } 
    }else{  
      for(r=1;r<nbRow;r++) {     
        for (c=0; c<nbCell; c++){            
			Table[r-1][c+2]=oTable.rows[r].cells[c].innerHTML;             
         }
         objet= oTable.rows[r].cells[index].innerHTML; 
        Table[r-1][0]=objet.replace(/<\/?[^>]+>/gi,""); 
        Table[r-1][1]=r;
      }  
    } 
    if(Dec){ 
        if(itype==1){ sortFunct=sort_intDesc; 
        }else{  sortFunct=sort_charDesc; } 
    }else{ 
        if(itype==1){ sortFunct=sort_int; 
        }else{ sortFunct=sort_char; }            
    }    
    //--- Tri Table ---//   
    Table.sort(sortFunct); 
    //---- Copier Table JavaScript dans Tableau Html ----// 
    if(navigator.appName=="Netscape"){ 
        for(r=1; r<nbRow; r++){     //De toutes les rangées          
            oTable.rows[r].innerHTML=Table[r-1][2];       
        }   
    }else{ 
      for(c=0; c<nbCell; c++){     
        for(r=1; r<nbRow; r++){     //De toutes les rangées          
            oTable.rows[r].cells[c].innerHTML=Table[r-1][c+2];         
        }        
      }   
    } 
} 

