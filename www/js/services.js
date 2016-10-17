//Math.floor(Math.random() * (max - (min - 1))) + min;

angular.module('starter.services', [])

.service('problemservice', function($rootScope, $localStorage) {
	this.generateProblem= function( level){
       // console.log($rootScope.level);
        var insteadlevel= $localStorage.level;
		var selectlevel=0;
    	var upperBound = 10;
    	var lowerBound = 2;
    	var op = "+";
        var oppar1="(";
        var oppar2=")";
    	var previousF=0, previousS=0, first=0, second=0;

  
    	if (insteadlevel==11) {
        	selectlevel=Math.floor(Math.random() * (10 - 6)) + 6;
    	}else if(insteadlevel==14){
            selectlevel=Math.floor(Math.random() * (13 - 11)) + 12;
        }else if(insteadlevel==16){
            var array16=[12,13,15];
            var level16=Math.floor(Math.random() * (2 + 1)) + 0;
            selectlevel=array16[level16];
        }
        else{
        	selectlevel=insteadlevel;
    	}

    	switch (selectlevel) {
        	case 2:
            	upperBound = 10;
            	op="-";
            	break;
        	case 3:
            	upperBound = 20;
            	op="+";
            	break;
        	case 4:
            	upperBound = 20;
            	op="-";
            	break;
        	case 5:
            	upperBound = 30;
            	op="+";
            	break;
        	case 6:
            	upperBound = 40;
            	op="+";
            	break;
        	case 7:case 8:case 9:case 10:
            	op="x";
            	break;
            case 12:
                upperBound = 5;
                lowerBound = 6;
                op='+';
                break;
            case 13:
                upperBound = 5;
                lowerBound = 6;
                op='-';
                break;
            case 14:
                upperBound = 10;
                lowerBound = 11;
                break;
            case 15:
                upperBound = 10;
                lowerBound = 11;
                op='x';
                break;
        	default:
             	op="+";
            	upperBound = 10;
            	break;
    	}

        if(insteadlevel == 14 || insteadlevel == 16){
            upperBound = 10;
            lowerBound = 11;
        }
        previousF= $localStorage.previousF;
        previousS= $localStorage.previousS;
  
    	var selectaa;
   		do{
       		selectaa=generatenumber(selectlevel,upperBound, lowerBound);
       		first=selectaa[0];
       		second=selectaa[1];
   		}while((previousF==first && previousS==second) || first==0 || second==0 || first==1 || second==1 || first==-1 || second== -1);

    		$localStorage.previousF=first;
    		$localStorage.previousS=second;

    		if (first < second && op=="-") {
            	var temp = first;
            	first = second;
           		 second = temp;
        	}

            if(second<0){
                oppar1='(';
                oppar2=')';
                if(op=='x') op='';
            } else {
                oppar1='';
                oppar2='';
                if(op=='x'){
                    oppar1='(';
                    oppar2=')';
                    op='';
                }
            }

    	var solution=0;

     	switch (op) {
        	case "-":
           		solution =first - second;
            	break;
        	case "x":
            	solution =first*second;
            	break;
            case "":
                solution =first*second;
                break;
        	default:
            	solution =first+second;
            	break;
    	}
        var problem={
            first: first,
            second: second,
            op: op,
            oppar1:oppar1,
            oppar2:oppar2,
            answer: solution
        }
        return JSON.stringify(problem);

    	// return {
     //    	first: first,
     //    	second: second,
     //    	op: op,
     //    	answer: solution
    	// };

	}

	var generatenumber= function(selectlevel, topvalue, bottomvalue){

    	var selectfirst=0;
    	var selectsecond=0;
    	var returnx=[];

    	switch(selectlevel){
        	case 1:case 3:case 5:case 6:
            	selectfirst=Math.floor(Math.random() * (topvalue - 2)) + 2;
            	selectsecond=Math.floor(Math.random() * (topvalue - 2)) + 2;    
            	break;
       		 case 2: case 4:
        		selectfirst=Math.floor(Math.random() * (topvalue - 2)) + 2;
        		selectsecond=Math.floor(Math.random() * (topvalue - selectfirst+2)) + selectfirst+2;
       	 		break;
        	case 7:
            	selectfirst=Math.floor(Math.random() * (6 - 2)) + 2;
            	switch (selectfirst){
                	case 2:
                    	selectsecond=Math.floor(Math.random() * (10 - 6)) + 6;
                    	break;
                	case 3:
                    	selectsecond=Math.floor(Math.random() * (10 - 4)) + 4;
                    	break;
                	default :
                    	selectsecond=Math.floor(Math.random() * (10 - 3)) + 3;
            	}
            	break;
        	case 8:
            	selectfirst=Math.floor(Math.random() * (10 - 6)) + 6;
            	selectsecond=Math.floor(Math.random() * (10 - 6)) + 6;
            	break;
        	case 9:
            	selectfirst=Math.floor(Math.random() * (13 - 2)) + 2;
            	selectsecond=Math.floor(Math.random() * (13 - 11)) + 11;
            	break;
        	case 10:
            	selectfirst=Math.floor(Math.random() * (6 - 2)) + 2;
            	if(selectfirst==2){
                	selectsecond=Math.floor(Math.random() * (21 - 13)) + 13;
            	}else{
                	selectsecond=Math.floor(Math.random() * (17 - 13)) + 13;
            	}

            	break;
            case 12:case 13:case 15:
                selectfirst=Math.floor(Math.random() * (topvalue + bottomvalue) - topvalue);
                selectsecond=Math.floor(Math.random() * (topvalue + bottomvalue) - topvalue);
                break;
            
            // case 15:
            //     selectfirst=Math.floor(Math.random() * (13 - 2)) + 2;
            //     selectsecond=Math.floor(Math.random() * (13 - 11)) + 11;
            
        }
    	returnx[0]=selectfirst;
    	returnx[1]=selectsecond;
    	return returnx;


	}



}).service('problemservice17', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=generatenumber(selectlevel);

        var problem={
            first: selectaa[0],
            second: selectaa[1],
            third: selectaa[2],
            op: '+',
            answer: selectaa[0] + selectaa[1]+ selectaa[2]
        }
        return JSON.stringify(problem);

    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (15 - 0)) + 1;
        numbers[1]=0;
        numbers[2]=0;
        // get second number of problem
        do{
            numbers[1]=Math.floor(Math.random() * (15 - 0)) + 1;
        }while(numbers[1] == numbers[0]);
        //
        var matcharray=[5,10,15,20];
        // array for third number of problem
        // getting third number from this array
        var canarray=[];
        // length of canarray
        var count=-1;

        // making "canarray"
        for(var i=0; i<4;i++){
            if(matcharray[i]>numbers[0]){
                canarray.push(matcharray[i] - numbers[0]);
                count++;
            }
            if(matcharray[i]>numbers[1]){
                canarray.push(matcharray[i] - numbers[1]);
                count++;
            }
        }
        // getting thrid number of problem
        do{
            var insteadnumber=Math.floor(Math.random() * (count + 1)) + 0;
            numbers[2]=canarray[insteadnumber];
        }while(numbers[0]== numbers[2] || numbers[1]== numbers[2]);


        var postionarray=[0,1,2];
        

        var returnx=[];
        returnx[0]=0;
        returnx[1]=0;
        returnx[2]=0;
        // randomize position of numbers on problem
        for(var i=0;i<3;i++){
            var position=Math.floor((Math.random() * postionarray.length) + 0) ;
            position=postionarray[position];
            var index=postionarray.indexOf(position);
            
            postionarray.splice(index, 1);
            returnx[position] = numbers[i];

        }


        
        return returnx;

    }

}).service('problemservice18', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=generatenumber(selectlevel);
        var answer=selectaa[0];
        var op1= operationfunc();
        console.log("op1="+ op1);
        if(op1=='+'){
            answer +=selectaa[1];
        } else{
            answer -=selectaa[1];
        }
        var op2= operationfunc();
        console.log("op2="+ op2);
        if(op2=='+'){
            answer +=selectaa[2];
        } else{
            answer -=selectaa[2];
        }
        var problem={
            first: selectaa[0],
            second: selectaa[1],
            third: selectaa[2],
            op1: op1,
            op2: op2,
            answer: answer
        }
        return JSON.stringify(problem);

    }

    var operationfunc = function(){
        var randomop=Math.floor((Math.random() * 2 ) + 0) ;
        var operation = "+";
        if(randomop){
            operation='-';
        }
        return operation;
    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (15 - 0)) + 1;
        numbers[1]=0;
        numbers[2]=0;
        // get second number of problem
        do{
            numbers[1]=Math.floor(Math.random() * (15 - 0)) + 1;
        }while(numbers[1] == numbers[0]);

        do{
            numbers[2]=Math.floor(Math.random() * (15 - 0)) + 1;
        }while(numbers[1] == numbers[2] || numbers[0] == numbers[2]);


        return numbers;
        

    }
}).service('problemservice19', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=generatenumber(selectlevel);

        var answer=selectaa[0];
        var op= operationfunc();
        
        if(op=='+'){
            answer +=selectaa[1];
        } else{
            answer -=selectaa[1];
        }

        var op1= operationfunc();
        
        if(op1=='+'){
            answer +=selectaa[2];
        } else{
            answer -=selectaa[2];
        }
        var op2= operationfunc();
        
        if(op2=='+'){
            answer +=selectaa[3];
        } else{
            answer -=selectaa[3];
        }

        var problem={
            first: selectaa[0],
            second: selectaa[1],
            third: selectaa[2],
            fourth: selectaa[3],
            op: op,
            op1: op1,
            op2: op2,
            answer: answer
        }
        return JSON.stringify(problem);

    }

    var operationfunc = function(){
        var randomop=Math.floor((Math.random() * 2 ) + 0) ;
        var operation = "+";
        if(randomop){
            operation='-';
        }
        return operation;
    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (15 - 0)) + 1;
        numbers[1]=0;
        numbers[2]=0;
        numbers[3]=0;
        // get second number of problem
        do{
            numbers[1]=Math.floor(Math.random() * (15 - 0)) + 1;
        }while(numbers[1] == numbers[0]);
        // third number
        if(numbers[0]>9 && numbers[1]>9){
            do{
                numbers[2]=Math.floor(Math.random() * (9 - 0)) + 1;
            }while(numbers[1] == numbers[2] || numbers[0] == numbers[2]);
        } else{
            do{
                numbers[2]=Math.floor(Math.random() * (15 - 0)) + 1;
            }while(numbers[1] == numbers[2] || numbers[0] == numbers[2]);
        }
        
        //
        var matcharray=10;
        // array for third number of problem
        // getting third number from this array
        var canarray=[];
        
        

        // making "canarray"
        for(var i=0; i<3;i++){
            if(numbers[i]<10){
                canarray.push(10 - numbers[i]);
            }
        }
        // length of canarray
        var count = canarray.length;
        // getting fourth number of problem
        //do{
            var insteadnumber=Math.floor(Math.random() * count) + 0;
            numbers[3]=canarray[insteadnumber];
        //}while(numbers[0]== numbers[3] || numbers[1]== numbers[3] || numbers[2]== numbers[3]);


        var postionarray=[0,1,2,3];
        

        var returnx=[];
        returnx[0]=0;
        returnx[1]=0;
        returnx[2]=0;
        returnx[3]=0;
        // randomize position of numbers on problem
        for(var i=0; i<4; i++){
            var position=Math.floor((Math.random() * postionarray.length) + 0) ;
            position=postionarray[position];
            var index=postionarray.indexOf(position);
            
            postionarray.splice(index, 1);
            returnx[position] = numbers[i];

        }


        
        return returnx;

    }

}).service('problemservice20', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=generatenumber(selectlevel);

        var answer=selectaa[0] * selectaa[1] * selectaa[2];
        

        var problem={
            first: selectaa[0],
            second: selectaa[1],
            third: selectaa[2],
            op: 'x',
            op1: 'x',
            answer: answer
        }
        return JSON.stringify(problem);

    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        var firstarray=[2,3,4,5,6,7,8,9,10,11,12,13,14,15,20,25];
        var pos=Math.floor(Math.random() * (15 + 1)) + 0;
        numbers[0] = firstarray[pos];
        numbers[1]=0;
        numbers[2]=0;
        
        // get second number of problem
        var secondarray = [2,3,4,5,6,8,10,20];
        do{
            pos=Math.floor(Math.random() * (7 + 1)) + 0;
            numbers[1] = secondarray[pos];
        }while(numbers[1] == numbers[0]);
        // third number
        
        
        //
        var matcharray=[10,20,30,40,50];
        // array for third number of problem
        // getting third number from this array
        var canarray=[];
        
        

        // making "canarray"
        for(var i=0; i<5;i++){
            if(!(matcharray[i]%numbers[1])){
                canarray.push(matcharray[i]/numbers[1]);
            }
        }
        // length of canarray
        var count = canarray.length;
        // getting fourth number of problem
        //do{
            pos=Math.floor(Math.random() * count) + 0;
            numbers[2]=canarray[pos];
        //}while(numbers[0]== numbers[3] || numbers[1]== numbers[3] || numbers[2]== numbers[3]);


        var postionarray=[0,1,2];
        

        var returnx=[];
        returnx[0]=0;
        returnx[1]=0;
        returnx[2]=0;
        
        // randomize position of numbers on problem
        for(var i=0; i<3; i++){
            var position=Math.floor((Math.random() * postionarray.length) + 0) ;
            position=postionarray[position];
            var index=postionarray.indexOf(position);
            
            postionarray.splice(index, 1);
            returnx[position] = numbers[i];

        }


        
        return returnx;

    }

}).service('problemservice21', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=generatenumber(selectlevel);

        
        var first=selectaa[1] * selectaa[2];
        var second= selectaa[0] * selectaa[2];
        var recursion= gcd(first, second);
        var answer= ''+first/recursion + '/' + second/recursion;


        var problem={
            first: first,
            second: second,
            op: '/',
            op1: '=',
            answer: answer
        }
        return JSON.stringify(problem);

    }
    var gcd = function(a, b){
        if(!b){
            return a;
        }
        return gcd(b, a%b);
    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (9 - 2)) + 3;
        
        
        // get second number of problem
       
            numbers[1]=Math.floor(Math.random() * ((numbers[0]-1) - 1)) + 2;

            numbers[2]=Math.floor(Math.random() * (10 - 1)) + 2;

       


        return numbers;
        

    }
}).service('problemservice22', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=[];
        do{
            selectaa=generatenumber(selectlevel);
            console.log("selectaa[1]="+selectaa[1]);

        } while(!selectaa[1]);
        

        
        var first=selectaa[1];
        var second= selectaa[0];
        var answer= (first/second).toFixed(2);
        answer*=50;


        var problem={
            first: first,
            second: second,
            op: '/',
            op1: '=',
            answer: answer
        }
        return JSON.stringify(problem);

    }
    var getcommonfunc = function(number){
        var commonlist=[];
        for(var i=2;i<=number/2;i++)
        {
            if(number%i === 0)
            {
                commonlist.push(i);
            }
        }
        return commonlist;
    }

    var getmatchlistfunc= function(mainnumber, comlists){
        var lists=[];
       // comlists=comlists.split(',');
        
        for(var ii=2; ii<=mainnumber; ii++){
            var lengthcommon=comlists.length;
            var count=0;
            if(comlists[0]!=''){
                for(var jj=0; jj<lengthcommon; jj++){
                    if(ii%comlists[jj]==0){
                        count++;
                    }
                }
            } else{
                count=0;
            }

            if(count==0){
                lists.push(ii);
            }
        }


        return lists;
    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (100 - 2)) + 3;
        
        
        // get second number of problem
       
            numbers[1]=Math.floor(Math.random() * ((numbers[0]-1) - 1)) + 2;
        // get aliquot of denominator    
            var commonlist= getcommonfunc(numbers[0]);
        // get list in whcih numerator can be.
            var matchlist= getmatchlistfunc(numbers[1], commonlist);
                         
        // get random number of matchlist
            var ordersecond = Math.floor(Math.random() * ((matchlist.length - 1) + 1)) + 0;
            numbers[1]= matchlist[ordersecond];

        return numbers;
        

    }
}).service('problemservice23', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=[];
        do{
            selectaa=generatenumber(selectlevel);
           
            
        } while(!selectaa[1]);
        var signs=['', '-'];
        var signpos=  Math.floor(Math.random() * (1 + 1)) + 0;
        var op2= signs[signpos];

        
        var first=op2+selectaa[1];
        var second= selectaa[0];
        var aaaa= (first/second).toFixed(2);
        
        var int1=1;
        var answer=(1 + parseFloat(aaaa)).toFixed(2)*25;
        //var answer=(int1.toFixed(2) + parseFloat(aaaa))*25;
        


        var problem={
            first: first,
            second: second,
            op: '/',
            op1: '=',
          //  op2: op2,
            answer: answer
        }
        return JSON.stringify(problem);

    }
    var getcommonfunc = function(number){
        var commonlist=[];
        for(var i=2;i<=number/2;i++)
        {
            if(number%i === 0)
            {
                commonlist.push(i);
            }
        }
        return commonlist;
    }

    var getmatchlistfunc= function(mainnumber, comlists){
        var lists=[];
       // comlists=comlists.split(',');
        
        for(var ii=2; ii<=mainnumber; ii++){
            var lengthcommon=comlists.length;
            var count=0;
            if(comlists[0]!=''){
                for(var jj=0; jj<lengthcommon; jj++){
                    if(ii%comlists[jj]==0){
                        count++;
                    }
                }
            } else{
                count=0;
            }

            if(count==0){
                lists.push(ii);
            }
        }


        return lists;
    }

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (10 - 2)) + 3;
        
        
        // get second number of problem
       
            numbers[1]=Math.floor(Math.random() * ((numbers[0]-1) - 1)) + 2;
        // get aliquot of denominator    
            var commonlist= getcommonfunc(numbers[0]);
        // get list in whcih numerator can be.
            var matchlist= getmatchlistfunc(numbers[1], commonlist);
                         
        // get random number of matchlist
            var ordersecond = Math.floor(Math.random() * ((matchlist.length - 1) + 1)) + 0;
            numbers[1]= matchlist[ordersecond];

        return numbers;
        

    }
}).service('problemservice24', function($rootScope, $localStorage) {
    this.generateProblem= function( level){
        var insteadlevel= $localStorage.level;
        var selectlevel=insteadlevel;
        var selectaa=[];
        
        selectaa=generatenumber(selectlevel);
        
        var signpos=  Math.floor(Math.random() * (1 + 1)) + 0;
        var insteadanswer = selectaa[1]/selectaa[0];
        if(signpos==0){
            if(insteadanswer > 0.5) {
                answer='>';
            } else if(insteadanswer == 0.5){
                answer= '='
            } else {
                answer='<';
            }
        } else{
            if(insteadanswer > 0.5) {
                answer='<';
            } else if(insteadanswer == 0.5){
                answer= '='
            } else {
                answer='>';
            }
        }
        
        
        //var answer=(int1.toFixed(2) + parseFloat(aaaa))*25;
        


        var problem={
            first: selectaa[1],
            second: selectaa[0],
            op: '/',
            op1: '___',
            op2: signpos,
            answer: answer
        }
        return JSON.stringify(problem);

    }
    var getMinMax = function(seletednumber){
        var minmax=[];
        if(seletednumber <= 9){
            minmax[0]=1;
            minmax[1]=seletednumber - 1;
        } else{
            var mediumnumber= Math.ceil(seletednumber/2);
            minmax[0]= mediumnumber - 5;
            minmax[1]= mediumnumber + 5;
        }
        return minmax;
    }
   

    var generatenumber= function(selectlevel){
        //number array for problem
        var numbers=[];
        // first number of problem
        numbers[0]=Math.floor(Math.random() * (100 - 1)) + 2;
        
        
        // get min and max value second number
        var minmax= getMinMax(numbers[0]);
        numbers[1]= Math.floor(Math.random() * (minmax[1] - (minmax[0] - 1))) + minmax[0];
        return numbers;
        

    }
})
;
