using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	public Player_Info player_info_ = new Player_Info();
	//Network client_ = null;

	// Use this for initialization
	void Start ()
	{
		//client_ = GameObject.Find ("Network Manager").GetComponent<Network> ();
	}
	
	// Update is called once per frame
	void Update ()
	{
		player_info_.x_ = player_info_.x_ + (player_info_.velocity_x_ * Time.deltaTime);
		player_info_.y_ = player_info_.y_ + (player_info_.velocity_y_ * Time.deltaTime);
		transform.position = new Vector3(player_info_.x_, player_info_.y_);
		Debug.Log (player_info_.x_ + ", " + player_info_.y_ + "," + Time.deltaTime);
	}
}
