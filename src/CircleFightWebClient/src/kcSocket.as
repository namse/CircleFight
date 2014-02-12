package
{
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.events.ProgressEvent;
	import flash.events.SecurityErrorEvent;
	import flash.net.Socket;
	import flash.system.Security;
	import flash.utils.ByteArray;

	public class kcSocket
	{
		private var socket:Socket = new Socket();
		
		public function kcSocket()
		{
			Security.allowDomain("*");
			
			socket.addEventListener(Event.CONNECT, onConnect);
			socket.addEventListener(Event.CLOSE, onClose);
			socket.addEventListener(IOErrorEvent.IO_ERROR, onError);
			socket.addEventListener(ProgressEvent.SOCKET_DATA, onResponse);
			socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, onSecError);
		}
		
		public function connectTo(addr:String, port:int):void
		{
			socket.connect(addr, port);
		}
		
		public function sendData(bytes:ByteArray)
		{
			trace("Socket Send Data");
			socket.writeBytes(bytes);
			socket.flush();
			trace(bytes);
		}
		
		private function onConnect(e:Event):void
		{
			trace("Socket Connected");
		}
		
		private function onClose(e:Event):void
		{
			trace("Socket Closed");
			socket.close();
		}
		
		private function onError(e:Event):void
		{
			trace("IO Error : "+e);
		}
		
		private function onResponse(e:Event):void
		{
			
		}
		
		private function onSecError(e:Event):void
		{
			trace("Security Error : "+e);
		}
	}
}