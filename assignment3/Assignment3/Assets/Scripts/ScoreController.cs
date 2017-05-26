using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreController : MonoBehaviour {
    public static ScoreController scoreController;
    private int score = 0;
    private UI_Manager uiManager;

	// Use this for initialization
	void Awake () {
        if (scoreController == null) {
            DontDestroyOnLoad(gameObject);
            scoreController = this;
        }
	}

    void Start() {
        uiManager = GameObject.Find("Canvas").GetComponent<UI_Manager>();
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    public int getScore() {
        return score;
    }

    public void addScore(string message, int value) {
        score += value;

        if (uiManager != null) {
            uiManager.addScore(message, value, score);
        }
    }
}
