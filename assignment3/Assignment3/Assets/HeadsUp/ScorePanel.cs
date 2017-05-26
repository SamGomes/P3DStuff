using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScorePanel : MonoBehaviour {

    private UI_Manager uiManager;
    public Text newScoreText;
    public Text newScoreScore;

    void Start() {
        uiManager = GameObject.Find("Canvas").GetComponent<UI_Manager>();
    }

    public void endScoreAnimation() {
        uiManager.endScoreAnimation();
    }
}
