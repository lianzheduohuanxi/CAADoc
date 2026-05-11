---
```vbscript
title: "How to use the Identity Card Interface"
category: "use case"
module: "CAADkiUseCases"
tags: ["CAADkiNotesTab", "CAADkiIdentityCard", "CAAVPMDesktop"]
source_file: "Doc/online/CAADkiUseCases/CAADkiIdentityCard.htm"
converted: "2026-05-11T17:33:45.939442"
```

---
tags: ["CAADkiNotesTab", "CAADkiIdentityCard", "CAAVPMDesktop"]
source_file: "Doc/online/CAADkiUseCases/CAADkiIdentityCard.htm"
converted: "2026-05-11T17:33:45.939442"
ENOVIA Lifecycle Applications |  User Interface |  How to use the Identity Card Interface _Creating and displaying tabs in ENOVIA_

converted: "2026-05-11T17:33:45.939442"
ENOVIA Lifecycle Applications |  User Interface |  How to use the Identity Card Interface _Creating and displaying tabs in ENOVIA_
Use Case

* * *

Abstract This article shows how to use the ENOVIIdentityCardInterface interface of the VPMDesktop framework to create and display tabs in the Identity Card View.

  * **What You Will Learn With This Use Case**
  * **The CAADkiIdentityCard Use Case**
    * What Does CAADkiIdentityCard Do?
    * How to Launch CAADkiIdentityCard
    * Where to Find the CAADkiIdentityCard Code
  * **Step-by-Step**
  * **In Short**

---

* * *

What You Will Learn With This Use Case This use case is intended to show you how to create and display a new tab for the Identity Card view in the Change Management domain. Identity Cards are used to control and display the data of an object. The VPMDesktop framework contains the _ENOVIIdentityCardInterface_ interface which allows you to directly create and display the tab which may then be manipulated as desired. [Top] The CAADkiIdentityCard Use Case CAADkiIdentityCard is a use case of the CAAVPMDesktop.edu framework that illustrates the creation and display of tabs for the Identity Card view of ENOVIA objects. [Top] What Does CAADkiIdentityCard Do? CAADkiIdentityCard is illustrating an example for a customer having a request from their user community to provide an informal way for each user to store personal notes connected to an ENOVIA object.  For purposes of illustration we will assume that the requirement is to only display these notes for Change Management objects (Actions/COs/CRs).  The information will be displayed by creating a new tab attached to the Identity Card view.  All data displayed on the tab will be stored locally on the user's workstation.  The _ENOVIIdentityCardInterface_ interface/methods shown are as follows:

  * **_ENOVIIdentityCardInterface_ - `isEnabled`**
  * **_ENOVIIdentityCardInterface_ - `setObject`**
  * **_ENOVIIdentityCardInterface_ - `setServerParameters`**

The _CAADkiNotesTab_ methods shown are as follows:

  * **_CAADkiNotesTab_ - `canEnabled`**
  * **_CAADkiNotesTab_ - `showMyView`**
  * **_CAADkiNotesTab_ - `CAADkiNotesTab`**
  * **_CAADkiNotesTab_ - `getFile`**

The _ActionListener_ interface/methods shown are as follows:

  * **_ActionListener_ - `actionPerformed`**

[Top] How to Launch _CAADkiIdentityCard_ To launch _CAADkiIdentityCard_ , you will need to execute the following steps:

  * Set up the build time environment [1]
  * Compile CAADkiNotesTab.java along with its prerequisites
  * Set up the run time environment
  * Modify the IdentityCardView.properties file declaring an additional view for _CAADkiNotesTab_ to point to the new java class
  * Modify the VPMIdentityCard_en.properties file to declare a title for the new tab represented by the _CAADkiNotesTab_ class
  * Launch ENOVIA LCA, create a Change Management object (Action/CO/CR) and select the object to display the Identity Card view
  * Enter data on the "My Notes" tab and select the Save button.

[Top] Where to Find the _CAADkiIdentityCard_ Code The CAADkiIdentityCard use case is made of a single file located in the CAADkiIdentityCard.mj module of the CAAVPMDesktop.edu framework: Windows | `InstallRootDirectory\CAAVPMDesktop.edu\CAADkiIdentityCard.mj\`
---|---
Unix | `InstallRootDirectory/CAAVPMDesktop.edu/CAADkiIdentityCard.mj/`
Unix | `InstallRootDirectory/CAAVPMDesktop.edu/CAADkiIdentityCard.mj/`
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step For demonstration purposes, the code from the CAADkiIdentityCard use case is shown here. There are three logical steps in the CAADkiIdentityCard use case:

  1. Create a Class Extending _JPanel_ and Implementing the _ENOVIIdentityCardInterface_
  2. Implement the _ENOVIIdentityCardInterface_ Methods
  3. Detailed Implementation of the `ShowMyView` Method
  4. Detailed Implementation of the Notes Data File

[Top] Create a Class Extending _JPanel_ and Implementing the _ENOVIIdentityCardInterface_

4. Detailed Implementation of the Notes Data File
        import com.dassault_systemes.vpmdesktop.vdk0interfaces.interfaces.ENOVIIdentityCardInterface;
        import com.dassault_systemes.vpmdesktop.vdk0interfaces.interfaces.ENOVIObject;
        import javax.swing.JPanel;

---
import com.dassault_systemes.vpmdesktop.vdk0interfaces.interfaces.ENOVIObject;
import javax.swing.JPanel;
These import statements are required for the following operations.

    //--- Create a class extending a JPanel implementing the ENOVIIdentityCardInterface
These import statements are required for the following operations.
```vbscript
          public class CAADkiNotesTab extends JPanel implements ENOVIIdentityCardInterface

```

          {
```vbscript
public class CAADkiNotesTab extends JPanel implements ENOVIIdentityCardInterface
              public CAADkiNotesTab() {}
              public void setServerParameters(String marker, String host) {}
              public boolean isEnabled(ENOVIObject obj) {}
              public void setObject(ENOVIObject obj) {}
              public static boolean canEnabled(ENOVIObject obj) {}

```

          }

---

  1. We create the **CAADkiNotesTab.java  **class skeleton to include a constructor **`CAADkiNotesTab`** and the methods copied from _ENOVIIdentityCardInterface_ **`setServerParameters`, `isEnabled`, **and **`setObject`.** The method **`canEnabled`** is not a true method in the interface since static methods can not be part of an interface but this method is also needed for our new class.
  2. The next method to implement is **`canEnabled`**.  This method is used to determine whether this tab should be added to the IdentityCard being constructed.  For our example we wish to add this new tab only to Actions, Change Orders and Change Requests.  To limit when this tab will be created we will need to get the Type from the ENOVIObject.
  3. The `setObject` method will be used to create the data and fields to be displayed on our new tab.

[Top] Implement the _ENOVIIdentityCardInterface_ Methods No additional import statements are required for the following operations.

    //--- implement ENOVIIdentityCardInterface::setServerParameters
```vbscript
    public void setServerParameters(String marker, String host) {}

```

    //--- implement CAADkiNotesTab::canEnabled

```vbscript
public void setServerParameters(String marker, String host) {}
        public static boolean canEnabled(ENOVIObject obj)

```

        {
            return ("ENOVIA_ECO"==obj.getBaseType() ||
                    "ENOVIA_ECR"==obj.getBaseType() ||
                    "ENOVIA_AFLAction"==obj.getBaseType());
        }

    //--- implement ENOVIIdentityCardInterface::isEnabled
        public boolean isEnabled(ENOVIObject obj)
        {
            return canEnabled(obj);
        }

    //--- implement ENOVIIdentityCardInterface::setObject
return canEnabled(obj);
```vbscript
        public void setObject(ENOVIObject obj)

```

        {
public void setObject(ENOVIObject obj)
            myObject = obj;
            String notes = myNotes.getProperty(obj.getInternalStringValue("V_name"));
            showMyView(notes);

        }

---

  1. The method `setServerParameters` is not needed for our example so we just use an empty method body.
  2. The _ENOVIObject_ interface includes the `getBaseType` method to return a string that can be used to determine what type of object is represented.  We can use this information in our implementation of the `canEnabled` method to limit when our new tab will be created.
  3. The `isEnabled` method determines when the user is allowed to select the tab for display and editing.  We will return TRUE whenever our new tab is created.
  4. The `setObject` method will do the main work of creating the layout of our new tab and populating the data to be displayed.

[Top] Detailed Implementation of the `ShowMyView` Method

4. The `setObject` method will do the main work of creating the layout of our new tab and populating the data to be displayed.
        import java.awt.BorderLayout;
        import java.awt.Color;
        import java.awt.Dimension;
        import java.awt.event.ActionEvent;
        import java.awt.event.ActionListener;

        import javax.swing.border.Border;
        import javax.swing.BorderFactory;
        import javax.swing.JButton;
        import javax.swing.JScrollPane;
        import javax.swing.JTextArea;

---
These import statements are required for the following operations.

These import statements are required for the following operations.
```vbscript
        private void showMyView(String notes)

```

        {
private void showMyView(String notes)
            Border raisedbevel, loweredbevel;

            raisedbevel     = BorderFactory.createRaisedBevelBorder();
```vbscript
```vbscript
            loweredbevel    = BorderFactory.createLoweredBevelBorder();

            myTextArea = new JTextArea(5, 30);
```

```

            myTextArea.setLineWrap(true);
            myTextArea.setBackground(Color.white);
            myTextArea.append(notes);
            JScrollPane scrollPane = new JScrollPane(myTextArea,
                                                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
                                                JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
            setPreferredSize(new Dimension(450, 110));
            scrollPane.setPreferredSize(new Dimension(500,250));
            scrollPane.setBorder(
                BorderFactory.createCompoundBorder(
                    BorderFactory.createCompoundBorder(
                                    loweredbevel,
                                    raisedbevel),
                    scrollPane.getBorder()));
            scrollPane.getHorizontalScrollBar().setEnabled(true);
            scrollPane.getVerticalScrollBar().setEnabled(true);
            add(scrollPane, BorderLayout.CENTER);

            JButton b1 = new JButton("Save");
            b1.setActionCommand("savenotes");
            b1.addActionListener(this);
            b1.setToolTipText("Click this button to save these notes.");

            add(b1, BorderLayout.SOUTH);

        }

---

```vbscript
        public class CAADkiNotesTab extends JPanel implements ENOVIIdentityCardInterface, **ActionListener**

public class CAADkiNotesTab extends JPanel implements ENOVIIdentityCardInterface, **ActionListener**
        public void actionPerformed(ActionEvent e)

```

        {
```vbscript
public class CAADkiNotesTab extends JPanel implements ENOVIIdentityCardInterface, **ActionListener**
public void actionPerformed(ActionEvent e)
            if ("savenotes".equals(e.getActionCommand()))

```

            {
```vbscript
public void actionPerformed(ActionEvent e)
if ("savenotes".equals(e.getActionCommand()))
```

```vbscript
                setNotes(myObject.getInternalStringValue("V_name"), myTextArea.getText());

```

            }
        }

---

  1. Inside the `showMyView`
  2. method we first create a _JTextArea_ for editing and displaying the notes text.  This _JTextArea_ is added to a _JScrollPane_ which is added to the _JPanel_ of _CAADkiNotesTab_ class.
  3. We need to have a way to trigger saving the text data so we are also adding a JButton.  To respond to the user selecting the Save button we need our class to implement _ActionListener_.
  4. To implement _ActionListener_ , we must add code to the `actionPerformed` method.  We will use this method the store the notes text in a file saved in the user's home directory.

[Top] Detailed Implementation of the Notes Data File

        import java.io.File;
        import java.io.FileInputStream;
        import java.io.FileOutputStream;
        import java.io.FileNotFoundException;
        import java.io.IOException;
        import java.util.Properties;
        import javax.swing.border.EtchedBorder;
        import javax.swing.border.TitledBorder;

---
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
These import statements are required for the following operations.

```vbscript
        public CAADkiNotesTab()

```

        {
These import statements are required for the following operations.
public CAADkiNotesTab()
            TitledBorder myBorder = new TitledBorder(new EtchedBorder(), myFullFilename);
            setBorder(myBorder);

            myFile = getFile();
            try

            {
```vbscript
setBorder(myBorder);
```vbscript
myFile = getFile();
```

try
                myNotes.load(new FileInputStream(myFile));
```

            }
myFile = getFile();
try
myNotes.load(new FileInputStream(myFile));
            catch(IOException e)

            {
                //e.printStackTrace();
                //No need to take any action since a file will be created when the notes are saved.
            }
        }

        private String getNotes(String key)
        {
            return myNotes.getProperty(key);
        }

private String getNotes(String key)
return myNotes.getProperty(key);
```vbscript
        private void setNotes(String key, String value)

```

        {
return myNotes.getProperty(key);
private void setNotes(String key, String value)
            myNotes.setProperty(key, value);
            try

            {
private void setNotes(String key, String value)
myNotes.setProperty(key, value);
try
                myNotes.store(new FileOutputStream(myFile),
                      myFileHeader);

            }
try
myNotes.store(new FileOutputStream(myFile),
myFileHeader);
            catch(IOException e)

            {
myNotes.store(new FileOutputStream(myFile),
myFileHeader);
catch(IOException e)
                e.printStackTrace();

            }
        }

e.printStackTrace();
        public File getFile() {
            if((myFilename==null) || (myFilename.length() == 0))
                myFile = null;
            else

            {
public File getFile() {
if((myFilename==null) || (myFilename.length() == 0))
myFile = null;
else
```vbscript
                myFile = new File(myDirectory, myFilename);

```

            }
myFile = null;
else
myFile = new File(myDirectory, myFilename);
            return myFile;

        }

---

  1. To simplify the file operations needed to read and store the notes text, we are using the standard Java properties class.
  2. We create a `getNotes` method to return the notes text based on the key.  This simple example is using the value stored in the V_name attribute as the key.
  3. The `setNotes` method is used to store the new or edited notes text into a Properties object and also saves the updated Properties information to a text file stored in the user's home directory on the client.

[Top]

* * *

In Short Use the _ENOVIIdentityCardInterface_ interface to create and display additional tabs in the Identity Card view for ENOVIA objects. You can hide the tab using ****`canEnabled`**** and disable the tab using ****`isEnabled`**.** [Top]

* * *

References [1] | [Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[Top]

* * *

History Version: **1** [Nov 2004] | Document created
---|---
[Top]

* * *

_Copyright 1994-2004, Dassault Systmes. All rights reserved._
