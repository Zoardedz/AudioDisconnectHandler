package;

import AudioManager.DisconnectReason;

class Main {
  static function main() {
    var am:AudioManager = null;
    AudioManager.CreateInstance(am);
    trace(am);
    //
    while (true){ 
      
    }
  }

  private static function revert(thing:Int):DisconnectReason{
    return switch(thing){
      case 0:
        DisconnectReasonDeviceRemoval;
      case 1:
        DisconnectReasonServerShutdown;
      case 2:
        DisconnectReasonFormatChanged;
      case 3:
        DisconnectReasonSessionLogoff;
      case 4:
        DisconnectReasonSessionDisconnected;
      case 5:
        DisconnectReasonExclusiveModeOverride;
      default:
        null;
    }
  }

  public static function imhavingsex(reasonIndex:Int){
    var audioDisconnectReason = revert(reasonIndex);
    trace(audioDisconnectReason);
  }
}

/*package;

import haxe.macro.Context;
import haxe.macro.Expr;
import haxe.macro.TypeTools;

class Main {
  macro static function main() {
    var fields = [
      { name: "x", type: TType.TInt },
      { name: "y", type: TType.TInt }
    ];
    
    var className = "MyClass";
    var classExpr = macro class $className 
	  {
		public var x:Int = 10;
		public var y:Int = 20;
        public function new() {}
      };
    
    // Call the macro and get the generated class expression
    var classDef = macro classExpr;
    var generatedExpr = Context.makeExpr(classDef, Context.currentPos());
    
    // Define the generated class
    var generatedType = Context.defineType(className, generatedExpr);
    var generatedClass = TypeTools.getClass(generatedType);
    
    // Use the generated class
    var instance = new $generatedClass();
    instance.x = 10;
    instance.y = 20;
    trace(instance.x); // Output: 10
  }
}

enum TType {
  TInt;
}*/