using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EndMenuManager : MonoBehaviour {
    public Image newHighscorePanel;
    public Image topHighscorePanel;

    // Use this for initialization
    public void changePanels() {
        newHighscorePanel.GetComponent<Animator>().SetBool("move", true);
        topHighscorePanel.GetComponent<Animator>().SetBool("move", true);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
