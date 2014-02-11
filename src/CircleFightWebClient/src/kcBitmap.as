package
{
	import flash.display.*;
	import flash.events.*;
	import flash.net.URLRequest;
	
	import CircleFightWebClient;

	public class kcBitmap
	{
		public function kcBitmap()
		{
		}
		
		private var orgbitmap:Bitmap = null;
		private var bitmap:Bitmap = null;
		private var orgbitmapData:BitmapData;
		private var bloaded:Boolean = false;
		
		private var loader:Loader = new Loader();
		public function Load(string:String):void
		{
			loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onLoadComplete);
			loader.load(new URLRequest(string));
			bloaded = false;
		}
		//"http://blogfiles.naver.net/20131022_61/apple2pcs_1382411972502uvuOo_JPEG/elsa_1920-1200.jpg"
		public function onLoadComplete (event:Event):void
		{
			orgbitmap = Bitmap(LoaderInfo(event.target).content);
			orgbitmapData = orgbitmap.bitmapData;
			bloaded = true;
		}
		
		public function DrawBitmap(w:int, h:int):void
		{
			if(bloaded)
			{
				bitmap = new Bitmap(orgbitmapData);
				bitmap.width = w;
				bitmap.height = h;
				
				CircleFightWebClient.STAGE.addChild(bitmap);
			}
		}
	}
}