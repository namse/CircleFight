//------------------------------------------------------------------------------
// <auto-generated>
//     이 코드는 도구를 사용하여 생성되었습니다.
//     런타임 버전:4.0.30319.18449
//
//     파일 내용을 변경하면 잘못된 동작이 발생할 수 있으며, 코드를 다시 생성하면
//     이러한 변경 내용이 손실됩니다.
// </auto-generated>
//------------------------------------------------------------------------------
using System;
using packet_type;
using UnityEngine;
namespace Handler
{
	public class MoveStopResultHandler
	{
		Player player = null;

		public MoveStopResultHandler ()
		{
			
		}
		
		public void Handle(MoveStopResult move_stop_result)
		{
			player = GameObject.Find (move_stop_result.player_id.ToString ()).GetComponent<Player> ();
			player.player_info_.SetPosition (move_stop_result.position_x, move_stop_result.position_y, player.transform);
			player.player_info_.SetVelocity (0, 0);

			Debug.Log ( "move_stop_result");
			Debug.Log ( "player_id : " + move_stop_result.player_id);
			Debug.Log ( "position_x : " + move_stop_result.position_x);
			Debug.Log ( "position_y : " + move_stop_result.position_y);
		}
	}
}



