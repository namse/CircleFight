using UnityEngine;
using System.Collections;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class Other_Player : MonoBehaviour {
	Player_Info player_info_ = new Player_Info();
	Network client_ = null;
	
	// Use this for initialization
	void Start ()
	{
		client_ = GameObject.Find ("Network Manager").GetComponent<Network> ();
		//Init (0, 0, 0, 0, 0, 0);
	}
	
	// Update is called once per frame
	void Update ()
	{
		transform.Translate (Vector3.right * player_info_.velocity_x_ * Time.deltaTime);
		transform.Translate (Vector3.right * player_info_.velocity_y_ * Time.deltaTime);
		
		player_info_.velocity_x_ = player_info_.velocity_x_ + player_info_.acceleration_ * Time.deltaTime;
		player_info_.velocity_y_ = player_info_.velocity_y_ + player_info_.acceleration_ * Time.deltaTime;

		if (Input.GetMouseButtonUp (0))
		{
			player_info_.SetPosition(0.5f, -0.5f, this.transform);
		}
	}
}
