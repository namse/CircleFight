using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
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
		Movement ();
		/*
		transform.Translate (Vector3.right * velocity_x_ * Time.deltaTime);
		transform.Translate (Vector3.right * velocity_y_ * Time.deltaTime);
		
		velocity_x_ = velocity_x_ + acceleration_ * Time.deltaTime;
		velocity_y_ = velocity_y_ + acceleration_ * Time.deltaTime;*/
	}

	void Movement()
	{
		if(Input.GetKey(KeyCode.W))
		{
			transform.Translate(Vector2.up * 3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * 3 * Time.deltaTime);
		}
		else if(Input.GetKey(KeyCode.S))
		{
			transform.Translate(Vector2.up * -3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.up * -3 * Time.deltaTime);
		}

		if(Input.GetKey(KeyCode.A))
		{
			transform.Translate(Vector2.right * -3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * -3 * Time.deltaTime);
		}
		else if(Input.GetKey(KeyCode.D))
		{
			transform.Translate(Vector2.right * 3 * Time.deltaTime);
			Camera.main.transform.Translate(Vector2.right * 3 * Time.deltaTime);
		}
	}
}
