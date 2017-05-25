using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

[Serializable]
public class HighscoreData:IComparable<HighscoreData> {
    public string name;
    public int score;

    public int CompareTo(HighscoreData other)
    {
        return -1*score.CompareTo(other.score);
    }
}

public class EndMenuManager : MonoBehaviour
{
    public InputField nameInputField;
    public Button submitButton;
    public Text noHighscoreText;
    public Image newHighscorePanel;
    public Image topHighscorePanel;
    private int currentScore = 0;
    private int maxHighscorers = 5;

    private List<HighscoreData> highscoresList = new List<HighscoreData>() {
        new HighscoreData() {name =  "André Fonseca", score = 10000},
        new HighscoreData() {name =  "Tiago Almeida", score = 9500},
        new HighscoreData() {name =  "Samuel Gomes", score = 8200},
        new HighscoreData() {name =  "Daniel Rodrigues", score = 6900},
        new HighscoreData() {name =  "Miguel Duarte", score = 5800},
    };

    public List<Text> nameHighScore;
    public List<Text> scoreHighScore;

    private string highscoreSavePath = "highscore.sav";

    void Start() {
        //debugEraseHighscoresFile();

        //Reactivate cursor
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;

        GameObject scoreController = GameObject.Find("ScoreController");
        if (scoreController != null) {
            currentScore = scoreController.GetComponent<ScoreController>().score;
        }

        loadHighscores();
        
        if (currentScore < highscoresList[highscoresList.Count - 1].score)
        {
            updateHighscoresUI();
            newHighscorePanel.GetComponent<Animator>().SetBool("skip", true);
            topHighscorePanel.GetComponent<Animator>().SetBool("skip", true);
            GameObject.Find("SadAirHorn").GetComponent<AudioSource>().Play();
        }
        else {
            GameObject.Find("AirHorn").GetComponent<AudioSource>().Play();
            noHighscoreText.enabled = false;
        }

    }

    //Called by inputField
    public void onNameInputChanged() {
        submitButton.interactable = nameInputField.text.Length >= 1;
    }


    //Called by submit button
    public void changePanels()
    {
        HighscoreData newHighScore = new HighscoreData() { name = nameInputField.text, score = currentScore };
        highscoresList.Add(newHighScore);
        trimHighscoresList();
        updateHighscoresUI();

        //Change color of my score to red
        for (int i = 0; i < maxHighscorers; i++)
        {
            if (nameHighScore[i].text == nameInputField.text) {
                nameHighScore[i].color = new Color(1.0f, 0.0f, 0.0f);
                scoreHighScore[i].color = new Color(1.0f, 0.0f, 0.0f);
            }
        }

        newHighscorePanel.GetComponent<Animator>().SetBool("move", true);
        topHighscorePanel.GetComponent<Animator>().SetBool("move", true);
        GameObject.Find("AirHorn").GetComponent<AudioSource>().Play();
    }

    //Called by the play again button
    public void loadLevel(string levelName)
    {
        SceneManager.LoadScene(levelName);
    }

    //Called by the quit button
    public void quitGame()
    {
        Application.Quit();
    }

    private void updateHighscoresUI()
    {
        for (int i = 0; i < maxHighscorers; i++)
        {
            nameHighScore[i].text = highscoresList[i].name;
            scoreHighScore[i].text = "" + highscoresList[i].score;
        }

        saveHighscores();
    }

    private void trimHighscoresList() {
        highscoresList.Sort();
        int size = highscoresList.Count;

        if (size > maxHighscorers)
            highscoresList.RemoveRange(maxHighscorers, size-maxHighscorers);

    }

    private void debugEraseHighscoresFile()
    {
        if (File.Exists(Application.persistentDataPath + highscoreSavePath))
            File.Delete(Application.persistentDataPath + highscoreSavePath);
    }

    private void loadHighscores() {
        if (File.Exists(Application.persistentDataPath + highscoreSavePath)) {
            BinaryFormatter bf = new BinaryFormatter();
            FileStream file = File.Open(Application.persistentDataPath + highscoreSavePath, FileMode.Open);
            List<HighscoreData> loadedHighscores = (List <HighscoreData>)bf.Deserialize(file);
            file.Close();

            highscoresList= loadedHighscores;
        }

        trimHighscoresList();

    }

    private void saveHighscores()
    {
        trimHighscoresList();

        BinaryFormatter bf = new BinaryFormatter();
        FileStream file = File.Open(Application.persistentDataPath + highscoreSavePath, FileMode.OpenOrCreate);
        bf.Serialize(file, highscoresList);
        file.Close();
    }
}
