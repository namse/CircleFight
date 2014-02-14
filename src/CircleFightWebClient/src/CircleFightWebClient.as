package
{
	[SWF(width=800,height=600)]
	
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.utils.ByteArray;
	
	import CircularBuffer;
	
	import kcBitmap;
	
	import kcSocket;
	
	public class CircleFightWebClient extends Sprite
	{
		public static var socket:kcSocket = new kcSocket();
		public static var STAGE:Stage;
		public function CircleFightWebClient()
		{
			socket.connectTo("localhost", 9001);
			
			if(stage)
				init();
			else
				addEventListener(Event.ADDED_TO_STAGE, init, false, 0, true);
			
			// Stage Background Fill at Black
			var bg:Sprite;			
			function changeStageColor( color : uint ) : void {
				bg ||= new Sprite();
				bg.graphics.clear();
				bg.graphics.beginFill( color, 1 );
				bg.graphics.drawRect( 0,0, stage.stageWidth, stage.stageHeight );
				bg.graphics.endFill();
				stage.addChildAt(bg, 0);
			}
			changeStageColor(0x000000);
			
			// Load Bitmap and Draw
			var bit:kcBitmap = new kcBitmap();
			bit.Load("http://img2.ruliweb.daum.net/mypi/gup/a/12/9/o/8048081011.jpg");
			
			stage.addEventListener("click", onClick);
			function onClick(e:MouseEvent):void
			{
				// changeStageColor(0xFF0000);
				// bit.DrawBitmap(800, 600);
				var sizeof:ByteArray = new ByteArray();
				var cb:CircularBuffer = new CircularBuffer();
				sizeof.writeObject(cb);
				var bytes2:ByteArray = new ByteArray();
				bytes2.endian = "littleEndian";
				cb.size = sizeof.length;
				cb.type = 1;
				cb.x = 100;
				cb.y = 200;
				bytes2.writeObject(cb);				
				trace(bytes2);
				socket.sendData(bytes2);
				trace("Sended");
			}
			
			
			
			/*
			var bitmap:Bitmap;
			var bitmapData:BitmapData;
			
			var loader:Loader = new Loader();
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onComplete);
			loader.load(new URLRequest("http://blogfiles.naver.net/20131022_61/apple2pcs_1382411972502uvuOo_JPEG/elsa_1920-1200.jpg"));
			
			function onComplete (event:Event):void
			{
				bitmap = Bitmap(LoaderInfo(event.target).content);
				bitmap.width = 800;
				bitmap.height = 600;
				bitmapData = bitmap.bitmapData;
				
				stage.addChild(bitmap);
			}
			*/
		}
		
		private function init(e:Event=null):void
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			STAGE = stage;
		}
	}
}