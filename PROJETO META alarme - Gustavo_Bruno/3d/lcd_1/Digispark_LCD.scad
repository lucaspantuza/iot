// -------------------------------------------
//               Digispark LCD case
//                 by Jan-Willem
//
//                   28.04.2013  
// -------------------------------------------
//   17.05.2013 official release on thingiverse


//shape = "flat"; 
shape = "angle";

// outer size
boxx = 86;
boxy = 41;   // internal size = 41-2*1.5 = 38.0
boxz = 21;

wall = 1.5;

// LCD pcb
//pcblcdx = 80;
//pcblcdy = 36;
//pcblcdz = 1.8;  //thichness off PCB

// distance between LCD PCB screws
lcdscrewx = 75; 
lcdscrewy = 31;

// window for LCD
lcdx    = 72;
lcdy    = 25;

// LCD mounting holes
standz  =   5;        // height of the standoff
standr  = 2.5;       // 5 mm diameter
screwz = standz;  // depth of srew hole
screwr = 1.5;       // 3 mm hole size

// 4 pole connector size
cony =   10 + 1;
conz =  2.5 + 1;

conlocz = 8.5+standz;  // 8.5 mm above pcb
conlocy = 2; // 2 mm from centre of hole

$fn=12;


// make the module
translate([-boxx/2,-boxy/2,0]) frontplate();

// view only
//translate([-boxx/2,-boxy/2,boxz+10])# bottom();

// print bottom
//if (shape == "flat")
//    	{rotate([0,180,0])  translate([-boxx/2,-boxy/2,-wall])  bottom();}
//	else
//	{translate([boxx/2,-boxy/2,wall])  rotate([20,180,0])  bottom();}



// make standoff for LCD pcb
// ------------------------------
module standoff()
	{difference()
		{translate([0,0,0]) cylinder(r=standr,h=standz+wall);
		  translate([0,0,wall+standz-screwz]) cylinder(r=screwr,h=screwz+0.1);
		}
	}




// LCD case
// --------------------------
module frontplate()
	{difference()
		{ if (shape=="flat") {cube([boxx,boxy,boxz]);}
                     else                 {cube([boxx,boxy,boxz+20]);}

		// empty the inside of the box
		  translate([wall,wall,wall]) cube([boxx-2*wall,boxy-2*wall,boxz+20]); 

		// make LCD window
	 	  translate([(boxx-lcdx)/2,(boxy-lcdy)/2,-wall]) cube([lcdx,lcdy,3*wall]);

		// make hole for connector
		  translate([-wall,conlocy+(boxy-lcdscrewy)/2,conlocz+wall]) cube([3*wall,cony,conz]);

		// make box with angle 20 degrees
		if (shape == "angle")                              // remove part of the top
			{translate([-5,-5,29]) rotate([-20,0,0]) cube([boxx+10,boxy+10,boxz+10]); }

		}


// standoffs for LCD PCB
	translate([                (boxx-lcdscrewx)/2,                (boxy-lcdscrewy)/2,0]) standoff(); 
	translate([                (boxx-lcdscrewx)/2,lcdscrewy+(boxy-lcdscrewy)/2,0]) standoff();
	translate([lcdscrewx+(boxx-lcdscrewx)/2,                (boxy-lcdscrewy)/2,0]) standoff();
	translate([lcdscrewx+(boxx-lcdscrewx)/2,lcdscrewy+(boxy-lcdscrewy)/2,0]) standoff();


	}


// LCD bottom
// ---------------------------
module bottom()
	{ if (shape=="flat")
		{difference()
			{union()
				{cube([boxx,boxy,wall]);
	   		 	translate([wall,wall,-2]) cube([boxx-2*wall,boxy-2*wall,2+wall]);
				}
			translate([2*wall,2*wall,-2.1]) cube([boxx-4*wall,boxy-4*wall,2.1]);

			// remove the corners
			translate([0,0,-2.1]) cube([25,15,2.1]);
			translate([boxx-25,0,-2.1]) cube([25,15,2.1]);	
			translate([0,boxy-15,-2.1]) cube([25,15,2.1]);	
			translate([boxx-25,boxy-15,-2.1]) cube([25,15,2.1]);	
			}
		}
	   else { rotate([-20,0,0]) cube([boxx,boxy+3,wall]); 
		     translate([boxx/2-15,wall,            -wall-1.5]) cube([30,2,3]);
		     translate([boxx/2-15,boxy-wall-2,-16])          cube([30,2,3]);

		     translate([wall,22,-10]) rotate([-20,0,0])  cube([2,15,3]);	// con side
		     translate([boxx-wall-2,10,-6]) rotate([-20,0,0])  cube([2,25,3]);	
		   } // end of else			
	}








 