angular.module('starter.controllers', ['ionic','ngStorage','ngLoad', 'ngAnimate'])

.controller('MapviewController', function($scope, $stateParams, $state, $ionicScrollDelegate,$timeout, $window, $rootScope, $localStorage, $ionicPopup) {

	$timeout(function() {
        var scrollView = $ionicScrollDelegate.$getByHandle('page1');
        scrollView.scrollBottom(false);
        
    }, 10);
    var devicewidth=$window.innerWidth;
    
    var deviceheight=$window.innerHeight;
    var vh=deviceheight/100;
    var vw=devicewidth/100;
    var ratiovhvw=vh/vw;
    var ratioangle=180/3.14;
    var alpha1=Math.atan(7*ratiovhvw/25);
    var length= (7*vh/Math.asin(alpha1)).toFixed(1);
    $rootScope.vw= vw;
    $rootScope.vh= vh;
    $rootScope.length=length+'px';
    $rootScope.alpha1=alpha1*180/3.14;
    $rootScope.alpha2=360-$rootScope.alpha1;


    $scope.mapbarlists=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
      28,29,30,31,32];


    $scope.levelclick=function(e){
      //alert(e);
      if(e <= Number($localStorage.completedlevel) || !$localStorage.completedlevel){
        $rootScope.level=e;
        $localStorage.level=e;
        $state.go('game', {selectedlevel: e});
      } else {
         var alertPopup = $ionicPopup.alert({
          title: 'Warning!',
          template: 'Please select level less than '+$localStorage.completedlevel
         });
      }
      

    }

    $scope.animationfoot = function(){
       
      var footcss={};

       if($localStorage.completedlevel ){
          if(Number($localStorage.completedlevel) > Number($localStorage.level)){


            var top = angular.element(document.querySelector("#mapcircle"+$localStorage.completedlevel)).prop('offsetTop');
            var left = angular.element(document.querySelector("#mapcircle"+$localStorage.completedlevel)).prop('offsetLeft');
            console.log("completedlevel="+$localStorage.completedlevel + " top="+ top+ " left="+ left);
            angular.element("#locationimg").animate({left:left+'px', top : top - 11*vw +'px'},2000,'linear');
          }
        } else {
          var top = angular.element(document.querySelector("#mapcircle1")).prop('offsetTop');
          var left = angular.element(document.querySelector("#mapcircle1")).prop('offsetLeft');
         
           footcss={
            'top': top - 11*vw + 'px',
            'left': left + 'px'
            }
        }
     
        
      
      return footcss;
    }
    
 

    // $scope.scrollmap=function(){
    // 	if($ionicScrollDelegate.getScrollPosition().top<50){
    // 		// $(".page1").show();
    // 	 //  	var height=$(".page1").height();
    	 
    // 	 //  	$ionicScrollDelegate.scrollTo(0,height,false);

    // 	}
    
    // }
	 
})
.controller('GameController', function($scope, $stateParams, $state, $ionicScrollDelegate, $timeout, $interval, $window, $rootScope, $animate, $localStorage,
           problemservice, problemservice17, problemservice18, problemservice19, problemservice20, problemservice21, problemservice22, problemservice23,
           problemservice24) {
   $scope.list1s=[0,1,2,3,4,5,6];
   $scope.list2s=[1,2,3,4];
   $scope.listbutton1s=[1,3,5,7,9];
   $scope.listbutton2s=[2,4,6,8,0];
   $scope.listproblems=[0,1,2,3,4,5,6,7];
   $scope.listbuttons=[1,2,3,4,5,6,7,8,9,0];
   $scope.starlists = [];
  // $scope.starlists=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20];
   // $scope.arrowlists=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,,27,
   //    28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,
   //    67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99];
   $scope.arrowlists=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,,27,
      28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49];
    //  $scope.arrowlists=[0,1,2,3,4,5,6,7,8,9,10];

   $scope.timer=0;
   $scope.paused = true;
   $scope.answer='';
   $scope.addop=1;
   $scope.level= $stateParams.selectedlevel;
   $scope.axisflag=0;
   var correctcount=0;
   if($scope.level == 22){
    $scope.axisflag=1;
   } else if($scope.level == 23) {
      $scope.axisflag=2;
   } else if($scope.level == 24) {
      $scope.axisflag=3;
   }
   if($scope.level>20){
    $scope.addop=0;
   }
   $scope.arryproblems=[];
   var stackSize=0;

   var problemtime= 3000;
   //var arrayproblems=[];
   //$scope.arryproblems=[];
   // answer array
   var solutionQueue = [];
   var mytimeout, myproblemtime;
   var count=0;
   var nowdate= new Date();
   var nowtime= nowdate.getTime();
    $scope.onTimeout = function() {
      
      $scope.timer++;
      
     if($scope.paused){
         mytimeout = $timeout($scope.onTimeout, 1000);
     }

    };

    $scope.onTimeoutproblem = function() {
        
        if(stackSize<8){
          makeproblem();
        }else{
          
          stopTimer();
        }
        
      
      
     if($scope.paused){
         myproblemtime = $timeout($scope.onTimeoutproblem, problemtime);
     }

    };

    var stopTimer= function(){
      stackSize=0;
          $scope.arryproblems=[];
          $timeout.cancel(mytimeout);
          $timeout.cancel(myproblemtime);
          $scope.paused = false;
          $state.go('mapview');
    };
    
    var makeproblem= function(){
      var problem, insteadpro;
      if($scope.level<17){
        problem = JSON.parse(problemservice.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.oppar1+problem.second+problem.oppar2;
      } else if($scope.level==17){
        problem = JSON.parse(problemservice17.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op+problem.third;
      }else if($scope.level==18){
        problem = JSON.parse(problemservice18.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op1+problem.second+problem.op2+problem.third;
      }else if($scope.level==19){
        problem = JSON.parse(problemservice19.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op1+problem.third + problem.op2 + problem.fourth ;
      }else if($scope.level==20){
        problem = JSON.parse(problemservice20.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op1+problem.third ;
      }else if($scope.level==21){
        problem = JSON.parse(problemservice21.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op1 ;
      } else if($scope.level==22){
        problem = JSON.parse(problemservice22.generateProblem($scope.level));
        
        insteadpro=''+problem.first+problem.op+problem.second+problem.op1 ;
      }
      else if($scope.level==23){
        problem = JSON.parse(problemservice23.generateProblem($scope.level));
        insteadpro=''+problem.first+problem.op+problem.second+problem.op1 ;
      } else if($scope.level==24){
        problem = JSON.parse(problemservice24.generateProblem($scope.level));
        if(problem.op2==0){
          insteadpro=''+problem.first+problem.op+problem.second+problem.op1+'1/2';
        } else{
          insteadpro=''+'1/2'+problem.op1+problem.first+problem.op+problem.second;
        }
      }
        
        solutionQueue.push(problem.answer);
        $scope.arryproblems.push(insteadpro);
        if($scope.arryproblems.length == 1) {
         $scope.question= $scope.arryproblems[0];
        }
       
       stackSize++;
    }



    // $scope.problemanimation= function(e){
    //   var anmcss={
    //     'top': '60%'
    //   }
    //   $timeout(function() {
    //     return anmcss;
    //   }, 1000);
      
    // }
   $scope.animation= function(e){
    var animcss={};
    if(e>0){
      animcss= {
        '-webkit-animation': 'animationtop'+e,
        'animation': 'animationtop'+e,
        'top': 85 - e*10 + '%',
        'animation-duration': '1500ms',
        '-webkit-animation-duration': '1500ms',
        'z-index': 30 - e
      };
      // animcss= {
      //   'top': 85 - e*10 + '%',
      //   'z-index': 30 - e
      // }
    } else {
      var animcss={
        'display': 'none'
      };
    }
    
    return animcss;
   }

   
    $scope.$on("$ionicView.loaded",  function(){
      // makeproblem();
      
      $scope.paused=true;
      
      
      mytimeout = $timeout($scope.onTimeout, 1000);
      if($localStorage.pauseedflag == '1' && $localStorage.pauseedlevel == $localStorage.level){
        $scope.timer=$localStorage.timer;
        $localStorage.pauseedflag='0';
        $scope.arryproblems = $localStorage.arryproblems;
        solutionQueue = $localStorage.solutionQueue;
        correctcount = Number($localStorage.correctcount);
        $scope.question = $scope.arryproblems[0];
        for(var ii=0; ii<correctcount; ii++){
          $scope.starlists.push(ii+1);
        }
      } else{
        
        
        makeproblem();
        makeproblem();
      }

      
     // myproblemtime= $timeout($scope.onTimeoutproblem, problemtime);
    });

    $scope.clikedpause= function(){
      $localStorage.pauseedflag='1';
      $localStorage.pauseedlevel=$localStorage.level;
      $localStorage.correctcount=correctcount;
      $localStorage.solutionQueue=solutionQueue;
      $localStorage.arryproblems=$scope.arryproblems;
      $localStorage.timer=$scope.timer;
      $state.go('mapview');

    }

    $scope.keydivideclick= function(){
      $scope.answer += '/';
    }

    $scope.keyclick=function(e){
        $scope.answer += e;
    }
    $scope.keyaddclick=function(){
       // $scope.answer = '-' + $scope.answer;
       if($scope.answer.indexOf('-')>-1){
        var strans= $scope.answer.split("-");
          $scope.answer = strans[1];
       } else{
            $scope.answer = '-' + $scope.answer;
       }
    }
    $scope.arrowclick= function(e){

      if(solutionQueue[0] <= (e+5) && solutionQueue[0] >= (e - 5)){

        rightanswer();
      }
    }
    $scope.compareclick= function(e){
      if(e == solutionQueue[0]){
        rightanswer();
      }
    }

    $scope.enter= function() {
        

          if($scope.answer==solutionQueue[0]){
            rightanswer();
          }else{
            wronganswer();
          }
        
          $scope.answer = '';
    }
    $scope.swipefunc= function(){
      $scope.answer = '';
    }

    var rightanswer= function(){
      // $scope.arryproblems.shift();
      var currentdate= new Date();
      var currenttime= currentdate.getTime();
    //  problemtime= problemtime + Math.ceil(((currenttime - nowtime) - problemtime)*0.05);
      var differenttime= currenttime -nowtime;

      console.log(problemtime);
      nowtime= currenttime;

      if(differenttime<=2000){
        $scope.starlists.push(correctcount+1);
        $scope.starlists.push(correctcount+2);
        correctcount+=2;

      } else if(differenttime >2000 && differenttime<=3000){
        $scope.starlists.push(correctcount+1);
        correctcount+=1;
      }
       if(correctcount>=20){
        correctcount=0;
        $scope.starlists=[];
          if(Number($localStorage.completedlevel) <= Number($localStorage.level) || !$localStorage.completedlevel){
            $localStorage.completedlevel = Number($localStorage.level)+1;
            
          }
        $state.go('mapview');
       }
      // var delem= angular.element(document.querySelector('#problem0'));
      // delem.remove();
     // $timeout(function() {
        $scope.arryproblems.splice(0,1);
        
    //  }, 100);
     // $scope.arryproblems.splice(0,1);
      solutionQueue.shift();
      stackSize--;
      makeproblem();
      $scope.question= $scope.arryproblems[0];
      // if(stackSize == 0){
      //   var aa= document.getElementById('problem0');
      //   $animate.enabled(false, aa);
      //   makeproblem();
      // } else {
      //   $scope.question= $scope.arryproblems[0];
      // }
        
      
    }

    var wronganswer= function(){
      correctcount-=1;
      $scope.starlists.splice(correctcount,1);
    }
  

    

})
// .directive("moveto", function($rootScope, $localStorage){
//   return{
//     restrict: "A",
//     link: function(scope, elem, attrs){
//       if($localStorage.completedlevel){
//           // var top = angular.element(document.querySelector("#mapcircle"+$localStorage.completedlevel)).prop('offsetTop');
//           // var left = angular.element(document.querySelector("#mapcircle"+$localStorage.completedlevel)).prop('offsetLeft');
//           var top = angular.element("#mapcircle"+$localStorage.completedlevel).offset().top;
//           var left = angular.element("#mapcircle"+$localStorage.completedlevel).offset().left;
//           console.log("completedlevel="+$localStorage.completedlevel + " top="+ top+ " left="+ left);
        
//           $(elem).animate({left:left+'px', top : top+'px'},500,'linear');
//         }
       
      
//     }
//   }
// })

;




