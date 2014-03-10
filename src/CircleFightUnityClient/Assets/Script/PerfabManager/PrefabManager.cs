using UnityEngine;
using System.Collections;

public class PrefabManager : MonoBehaviour {
	public GameObject prefPlayer;

	// Use this for initialization
	void Start ()
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
}
