// Configuration sets up all the names for instances of each of the classes (motors or sensors)
vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::motor LeftMotor1 = vex::motor(vex::PORT13,true);
vex::motor LeftMotor2 = vex::motor(vex::PORT14,true);
vex::motor RightMotor1 = vex::motor(vex::PORT11,false);
vex::motor RightMotor2 = vex::motor(vex::PORT12,false);
vex::motor PuncherMotor = vex::motor(vex::PORT15, true);
vex::motor IntakeMotor = vex::motor(vex::PORT16,false);
vex::encoder LeftEncoder = vex::encoder(Brain.ThreeWirePort.G);
vex::encoder RightEncoder = vex::encoder(Brain.ThreeWirePort.A);
vex::gyro Gyro1 = vex::gyro(Brain.ThreeWirePort.D);
vex::gyro Gyro2 = vex::gyro(Brain.ThreeWirePort.C);
vex::limit PuncherLimit = vex::limit(Brain.ThreeWirePort.F);
vex::limit IntakeLimit = vex::limit(Brain.ThreeWirePort.E);