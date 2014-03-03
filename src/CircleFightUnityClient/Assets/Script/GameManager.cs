using UnityEngine;
using System.Collections;

public class GameManager : MonoBehaviour {
	public GameObject prefab_CircleFightResponeMenu;
	int GameStatus = 0;

	string string_id = "아이디";
	string string_pw = "비밀번호";

	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	// GUI
	void OnGUI()
	{
		// 로그인 UI
		if (GameStatus == 0)
		{
			string_id = GUI.TextField (new Rect ((Screen.width - 200) / 2, Screen.height / 2 + 30, 200, 20), string_id, 20);
			string_pw = GUI.TextField (new Rect ((Screen.width - 200) / 2, Screen.height / 2 + 60, 200, 20), string_pw, 20);

			if (GUI.Button (new Rect ((Screen.width - 200) / 2, Screen.height / 2 + 90, 200, 20), "Login"))
			{
				GameStatus = 1;

				Debug.Log ("Login Clicked!");
			}
		}
		// 서버로 부터 응답을 기다린다.
		else if (GameStatus == 1)
		{
			GameStatus = 2;

			// 응답이 오고, 필요한 패킷들을 모두 받은 후 로그인 UI를 삭제하고 리스폰 UI를 띄운다.
			Destroy(GameObject.Find ("CircleFightLoginUI"));
			Instantiate(prefab_CircleFightResponeMenu);
		}
		// 자신의 마지막 위치를 중심으로 시뮬레이션해주고, 리스폰 메뉴를 띄운다.
		else if (GameStatus == 2)
		{
		}
		// 게임 플레이 중 ...
		else if (GameStatus == 3)
		{
			
		}
	}
}
