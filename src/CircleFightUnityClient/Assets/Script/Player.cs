using UnityEngine;
using System.Collections;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class Player : MonoBehaviour {
	[System.Serializable]
	public struct Player_Info
	{
		public float x_;
		public float y_;
		public float velocity_x_;
		public float velocity_y_;
		public float acceleration_;
		public float angle_;
	}
	Player_Info player_info_ = new Player_Info ();
	Network client = new Network();
	
	// Use this for initialization
	void Start ()
	{
		client.Init ();
		Init (0, 0, 0, 0, 0, 0);
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
			SetPosition(0.5f, -0.5f);
			BinaryFormatter bf = new BinaryFormatter();
			MemoryStream ms = new MemoryStream();
			bf.Serialize(ms, player_info_);
			Debug.Log(ms.Length);
			client.writer.Write ((short)(4+ms.Length));
			client.writer.Write ((short)(1));
			client.writer.Write (ms.ToArray ());
			client.writer.Flush();
		}
	}
	
	public void Init(float x, float y, float velocity_x, float velocity_y, float acceleration, float angle)
	{
		SetPosition (x, y);
		SetVelocity (velocity_x, velocity_y);
		SetAcceleration (acceleration);
		SetAngle (angle);
	}
	
	public void SetPosition (float x, float y)
	{
		player_info_.x_ = x;
		player_info_.y_ = y;
		transform.position = new Vector3(player_info_.x_, player_info_.y_);
	}
	public void SetVelocity(float velocity_x, float velocity_y)
	{
		player_info_.velocity_x_ = velocity_x;
		player_info_.velocity_y_ = velocity_y;
	}
	public void SetVelocity_x(float velocity_x)
	{
		player_info_.velocity_x_ = velocity_x;
	}
	public void SetVelocity_y(float velocity_y)
	{
		player_info_.velocity_y_ = velocity_y;
	}
	public void SetAcceleration(float acceleration)
	{
		player_info_.acceleration_ = acceleration;
	}
	public void SetAngle(float angle)
	{
		player_info_.angle_ = angle;
		transform.rotation = Quaternion.AngleAxis (player_info_.angle_, Vector3.right);
	}
	
	public float GetAngle()
	{
		return player_info_.angle_;
	}
}
