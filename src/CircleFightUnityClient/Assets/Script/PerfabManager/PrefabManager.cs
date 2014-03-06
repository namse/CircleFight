using UnityEngine;
using System.Collections;

public class PrefabManager : MonoBehaviour {
	public GameObject prefPlayer;
	public GameObject prefOtherPlayer;

	// Use this for initialization
	void Awake ()
	{
	}

	// Update is called once per frame
	void Update ()
	{
	
	}
	
	public void InstantiatePlayer (int player_id)
	{
		Instantiate (prefPlayer, Vector3.zero, Quaternion.identity).name = player_id.ToString ();
	}
	
	public void InstantiateOtherPlayer (int player_id)
	{
		Instantiate (prefOtherPlayer, Vector3.zero, Quaternion.identity).name = player_id.ToString ();
	}
}
