using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreController : MonoBehaviour {
    public static ScoreController scoreController;

    public int score = 123456;

	// Use this for initialization
	void Awake () {
        if (scoreController == null) {
            DontDestroyOnLoad(gameObject);
            scoreController = this;
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
